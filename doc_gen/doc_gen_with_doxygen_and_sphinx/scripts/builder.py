
#! Base-class of a step, to define the steps for a builder
class StepBase:

    def __init__(self):
        self.myConfig = None

    def Setup(self, aConfig):
        self.myConfig = aConfig

    def Run(self):
        pass


#! Base-class of builder, to define a build procedure
class BuilderBase:

    def __init__(self):
        self.myArguments = None
        self.myConfig = None
        self.myParser = None
        self.mySteps = []

        self.SetupArgumentParser()
        self.SetupSteps()

    def SetupArgumentParser(self):
        # self.myParser = ArgumentParser()
        pass

    def SetupSteps(self):
        # self.mySteps.append(StepBase())
        pass

    def SetupDependencies(self):
        pass

    def Setup(self, aArguments):
        self.myArguments = aArguments
        self.myConfig = self.myParser.parse_args(args=aArguments)
        self.SetupDependencies()

    def Run(self):
        for step in self.mySteps:
            step.Setup(self.myConfig)
            step.Run()
