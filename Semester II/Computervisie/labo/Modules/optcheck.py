import os


def getArgument(args):
    try:
        filePath = args[1]
    except IndexError:
        print("One parameter required: the path of an image.")
        exit(-1)

    if (not os.path.isfile(filePath)):
        print("'" + filePath + "' is not an existing file.")
        exit(-1)
    return filePath
