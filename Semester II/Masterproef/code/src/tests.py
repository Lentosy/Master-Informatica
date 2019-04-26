import unittest
from classification_strategies import perFrameClassification, simpleBufferClassification
from classification import loadTrainingset, loadValidationset
from constants import PERSONS

class testClassificationStrategies(unittest.TestCase):

    def testPerFrameClassification(self):
        for i in range(1, len(PERSONS) + 1):
            testPersons = PERSONS[:i - 1] + PERSONS[i:]
            validationPerson = PERSONS[i - 1]
            trainingset = loadTrainingset(testPersons)
            validationset = loadValidationset(validationPerson)
            evaluateClassifiers(trainingset, validationset, perFrameClassification)

if __name__ == '__main__':
    unittest.main()