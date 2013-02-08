#!/usr/bin/env python

import os, string
import shutil, errno, sys

def findHeadersAndSources(includepath):
    headers = []
    sources = []
    for root,dir,files in os.walk(os.path.join(includepath, "lib/")):
        for file in files:
            extension = file.split('.')[-1]
            if extension=="h":
                headers.append(os.path.join(root,file))
            elif extension=="cpp":
                sources.append(os.path.join(root,file))
                
    return headers, sources

def getUsingLibs():
    return ["GL", "glfw", "GLEW", "assimp", "IL", "ILU"]

def makeMainFile(path, sceneName):
    sceneName = sceneName.replace(" ", "")
    
    scriptDir = os.path.dirname(sys.argv[0])
    tmplFile = open(os.path.join(scriptDir, "template_main.cpp"), 'r')
    template = tmplFile.readlines()
    content = map(lambda str: string.replace(str, "%SCENE_NAME%", sceneName), template)
    
    mainFile = open(os.path.join(path,"main.cpp"), 'w')
    mainFile.writelines(content)
    mainFile.close()

def makeProjectFile(path, name, includepath, sceneName):
    os.chdir(path)
    
    libs = getUsingLibs()
    headers, sources = findHeadersAndSources(includepath)
    
    projectFile = open(name, 'w')
    
    projectFile.write("TEMPLATE = app\n")
    
    projectFile.write("\n")
    for libName in libs:
        projectFile.write("LIBS += ")
        projectFile.write("-l"+libName+"\n")
        
    projectFile.write("\n")
    projectFile.write("INCLUDEPATH = "+includepath+"\n")
        
    projectFile.write("\n")
    projectFile.write("SOURCES += main.cpp \\\n")
    for source in sources:
        projectFile.write("    "+source+" \\\n")
    projectFile.write("    "+sceneName+".cpp\n")
    
    projectFile.write("\n")
    projectFile.write("HEADERS += \\\n")
    for header in headers:
        projectFile.write("    "+header+" \\\n")
    projectFile.write("    "+sceneName+".h\n")
        
    projectFile.close()
    
    os.chdir("..")
    
def makeSceneFiles(path, sceneName):
    
    sceneName = sceneName.replace(" ", "")
    sceneNameUpper = sceneName.upper()
    
    scriptDir = os.path.dirname(sys.argv[0])
    tmplFile = open(os.path.join(scriptDir, "template_scene.h"), 'r')
    template = tmplFile.readlines()
    content = map(lambda str: string.replace(str, "%SCENE_NAME%", sceneName), template)
    content = map(lambda str: string.replace(str, "%SCENE_NAME_UPPER%", sceneNameUpper), content)
    
    headerFile = open(os.path.join(path,sceneName+".h"), 'w')
    headerFile.writelines(content)
    headerFile.close()
    
    sourceFile = open(os.path.join(path,sceneName+".cpp"), 'w')
    sourceFile.writelines("#include \""+sceneName+".h\"\n")
    sourceFile.close()
    
def copyDirectory(src, dst):
    try:
        shutil.copytree(src, dst)
    except OSError as exc: # python >2.5
        if exc.errno == errno.ENOTDIR:
            shutil.copy(src, dst)
        else: raise
    
def makeProject(projectName, sceneName, includepath="../.."):
    scriptDir = os.path.dirname(sys.argv[0])
    
    if not os.path.exists(projectName): os.mkdir(projectName)
    
    makeProjectFile(projectName, projectName+".pro", includepath, sceneName)
    makeMainFile(projectName, sceneName)
    makeSceneFiles(projectName, sceneName)
    
    binPath = os.path.join(projectName, "bin")
    resourcePath = os.path.join(projectName, "bin/resources")
    if not os.path.exists(binPath): os.mkdir(binPath)
    copyDirectory(os.path.join(scriptDir, "template_resources"), resourcePath)
    
    
def main():
    
    projectName = raw_input("Insert project name: ")
    sceneName = raw_input("Insert scene name: ")
    
    makeProject(projectName, sceneName)
    

   
if __name__=="__main__":
    main()
