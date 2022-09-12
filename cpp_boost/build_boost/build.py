
import os
import sys
import platform
import subprocess
import time

##############################################################################
# configurations
##############################################################################
repo = 'https://github.com/boostorg/boost.git'
version = '1.79.0'
##############################################################################

tag = 'boost-{}'.format(version)
installDir = 'boost_{}'.format(version).replace('.', '_')

skipGitCheckout = '--skip-git-checkout' in sys.argv
dryRun = '--dry-run' in sys.argv
skipBootstrap = '--skip-bootstrap' in sys.argv
cleanup = '--cleanup' in sys.argv
buildStaticLibrary = '--static' in sys.argv
buildWithMultiThreaded = '--multi-threaded' in sys.argv

boostBuildScriptDir = os.path.abspath(os.path.dirname(__file__))
boostRepoDir = os.path.join(boostBuildScriptDir, 'boost')
boostBuildDir = os.path.join(boostBuildScriptDir, '.build')
boostInstallDir = os.path.abspath(os.path.join(boostBuildScriptDir, '..', installDir))
logFilePath = os.path.join(boostBuildScriptDir, 'build.log')

componentsToBuild = [
    'atomic',
    'chrono',
    'container',
    'context',
    'contract',
    'coroutine',
    'date_time',
    'exception',
    'fiber',
    'filesystem',
    'graph',
    'graph_parallel',
    'headers',
    'iostreams',
    'json',
    'locale',
    'log',
    'math',
    'mpi',
    'nowide',
    'program_options',
    # 'python',
    'random',
    'regex',
    'serialization',
    'stacktrace',
    'system',
    'test',
    'thread',
    'timer',
    'type_erasure',
    'wave',
]


SHELL_INTERNAL_ERROR_RETURN_CODE = -13131

from logging import DEBUG, StreamHandler, FileHandler, getLogger
logger = getLogger('boost_builder')
logger.addHandler(StreamHandler())
logger.addHandler(FileHandler(logFilePath, mode = 'w', encoding = 'utf-8'))
logger.level = DEBUG

logger.info("running {}".format(sys.argv[0]))
logger.info("repo {}".format(boostRepoDir))
logger.info("build in {}".format(boostBuildDir))
logger.info("install to {}".format(boostInstallDir))
logger.info("log into {}".format(logFilePath))
logger.info("options:".format())
logger.info("    --skip-git-checkout   : {}".format(skipGitCheckout))
logger.info("    --dry-run             : {}".format(dryRun))
logger.info("    --skip-bootstrap      : {}".format(skipBootstrap))
logger.info("    --multi-threaded(/MT) : {}".format(buildWithMultiThreaded))
logger.info("    --static              : {}".format(buildStaticLibrary))
logger.info("    --cleanup             : {}".format(cleanup))
time.sleep(5)


class BuildFailed(Exception):
    pass

class RunCommandLineFailed(BuildFailed):
    pass

def log(aMessage):
    global logger
    logger.info(aMessage)

def FakeRunner(aCommand):
    log(str(aCommand))
    return 0, aCommand, ''

def RunShellCommand(aCommand):
    log('executing shell command : {0}'.format(aCommand))
    if 'Windows' == platform.system():
        shell = True
    elif 'Linux' == platform.system():
        shell = False
    try:
        proc = subprocess.Popen(
            aCommand,
            stdout = subprocess.PIPE, stderr = subprocess.PIPE,
            shell = shell, universal_newlines = True
            # env = env,
        )
        stdout, stderr = proc.communicate()
        returncode = proc.returncode
    except Exception as err:
        stdout, stderr = '', '{}'.format(err)
        returncode = SHELL_INTERNAL_ERROR_RETURN_CODE
    if len(stdout) > 0:
        log(stdout)
    if len(stderr) > 0:
        log(stderr)
    return returncode, stdout, stderr

def RunShellCommandWithException(aCommand):
    returncode, stdout, stderr = RunShellCommand(aCommand)
    if 0 != returncode:
        raise RunCommandLineFailed("returncode {}, command {}".format(returncode, aCommand))

def ChangeDirectory(aDirectory):
    log('Entering {}'.format(aDirectory))
    os.chdir(aDirectory)

def BuildBoost():
    commandRunner = RunShellCommandWithException if not dryRun else FakeRunner

    if not os.path.exists(os.path.join(boostRepoDir, '.git')):
        commandRunner(['git', 'clone', repo, boostRepoDir])
        if dryRun:
            os.makedirs(boostRepoDir)

    ChangeDirectory(boostRepoDir)

    if cleanup:
        commandRunner(['git', 'clean', '-dfx'])
        commandRunner(['git', 'submodule', 'foreach', 'git', 'clean', '-dfx'])

    if not skipGitCheckout:
        commandRunner(['git', 'checkout', tag])
        commandRunner(['git', 'reset', '--hard'])
        commandRunner(['git', 'submodule', 'update', '--init', '--recursive'])

    if not skipBootstrap or cleanup:
        commandRunner(['bootstrap.bat'])

    b2BuildCommand = [
        'b2',
        '--prefix={}'.format(boostInstallDir),
        '--build-type=complete',
        '--build-dir={}'.format(boostBuildDir),
        'threading=multi',
        'toolset=msvc',
        'architecture=x86',
        'address-model=64',
        '--allow-shared-static'
    ]

    if buildStaticLibrary:
        b2BuildCommand.append('link=static')
    else:
        b2BuildCommand.append('link=shared')
    
    if buildWithMultiThreaded:
        b2BuildCommand.append('runtime-link=static') # /MT multi-threaded  ==>>> /MTd multi-threaded(debug)
    else:
        b2BuildCommand.append('runtime-link=shared') # /MD multi-threaded-dll ===>>>  /MDd multi-threaded-dll(debug)

    for component in componentsToBuild:
        b2BuildCommand.append('--with-{}'.format(component))

    commandRunner(b2BuildCommand + ['variant=release','install'])
    commandRunner(b2BuildCommand + ['variant=debug', 'install'])


if '__main__' == __name__:
    BuildBoost()
