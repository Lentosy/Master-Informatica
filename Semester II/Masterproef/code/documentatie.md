# Installatie

Voer eerst het `pip_install.py` script uit. Dit zal alle nodige libraries installeren op het toestel. De package PyKinectV2 bevat echter nog oude bestanden.
Kopieer daarom de folder `lib\pykinect2` naar de `site-packages` in de python distributie (default pad is `Python\Lib\site-packages\pykinect2`) en overschrijf de oude bestanden.

# Scripts

## pip_install.py

gebruik: python pip_install.py

Dit script installeert alle nodige modules die vereist zijn om het hoofdscript te runnen.

## main.py

gebruik: python main.py [-h | -d | record action_number person_number]

Dit script verwacht dat de kinect SDK 2.0 reeds geïnstalleerd is. Dit kan gedownload worden op https://www.microsoft.com/en-us/download/details.aspx?id=44561

Dit script zal altijd de kinect aanspreken en zijn kleuren, diepte en skeletbeelden opvragen. Afhankelijk van de argumenten wijzigt de functionaliteit:
    1) Indien er geen argumenten zijn wordt een default runtime opgestart. Deze omgeving zal enkel de kleurenbeelden van de kinect tonen en de skeletbeelden, als die er zijn.
    2) Het script opstarten met de -d optie start een debug runtime. Hierbij is het aantal frames per seconde veel lager (zie de DEBUG_FPS en DEFAULT_FPS constanten in `constants.py`). Ook wordt per frame de feature vector uitgeschreven van de head joint.
    3) Het script kent een subcommando _record_. Dit commando zal een omgeving starten waarmee beelden en skeletinformatie opgeslagen kunnen worden. Het subcommando verwacht twee positionele argumenten. Het eerste argument is een integer die de specifieke actie aanduidt die zal uitgevoerd worden. Het tweede argument is ook een integer die de persoon aanduidt die de actie uitvoert. Voer `python main.py record -h` uit om alle mogelijke integers te zien.

## compressor.py

Dit script wordt best uitgevoerd wanneer een dataset is opgenomen. Default wordt elke frame opgeslagen als een niet-gecompresseerd .bmp bestand zodat het schrijven naar de schijf de opname minimaal stoort. Deze bestanden zijn echter groot (~6MB per bestand) en worden daarom gecompresseerd naar .jpg bestanden, die ongeveer 500 KB groot zijn.

Dit script verwacht geen argumenten. Het zal elk bestand in de data/ folder die een .bmp extensie heeft omzetten naar een .jpg bestand.

## runtime.py

Dit bestand bevat de implementatie van de verschillende runtimes.