import subprocess
import sys

def install(package):
    subprocess.call([sys.executable, '-m' , 'pip', 'install', package])


packages = ['pykinect2', 'matplotlib', 'pygame', 'pandas']

for package in packages:
    install(package)