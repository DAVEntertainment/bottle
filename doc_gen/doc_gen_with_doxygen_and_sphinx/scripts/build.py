import sys
from builder import BuilderBase, StepBase
from argparse import ArgumentParser, RawTextHelpFormatter

#! Class StepTest
class StepTest(StepBase):
    
    def Run(self):
        print("run step test")
        if self.myConfig.myTest:
            print("test done")
        else:
            print("test ignored")


#! Class Builder
class Builder(BuilderBase):
    '''
    class Builder (from BuilderBase)
    '''

    def SetupArgumentParser(self):
        '''
        function SetupArgumentParser
        '''
        self.myParser = ArgumentParser()
        workflow = self.myParser.add_argument_group('workflow')
        workflow.add_argument(
            "--test", "-t",
            dest = 'myTest',
            help = "Test",
            default = False,
            action = 'store_true'
        )
    
    def SetupSteps(self):
        '''
        function SetupSteps
        '''
        self.mySteps.append(StepTest())

def main():
    '''
    main function of build in 
    '''
    pass

if '__main__' == __name__:
    builder = Builder()
    builder.Setup(sys.argv[1:])
    builder.Run()

