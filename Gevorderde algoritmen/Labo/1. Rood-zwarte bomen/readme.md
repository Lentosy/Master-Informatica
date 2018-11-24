[Opgave](https://github.com/Lentosy/Master-Informatica/blob/master/Gevorderde%20algoritmen/Labo/1.%20Rood-zwarte%20bomen/Opgave/opgave.md)

# Werking
### main.cpp
Bevat twee functies, de `void main()` functie en `void tekenBoom(RZWboom<Sleutel>& boom, bool open_bestand)` functie.

De `main` functie maakt eerst een vector met 3 innerlijke vectoren aan, die alle sleutels in level order voor drie bomen bevat. De tweede vector zijn stellen dezelfde boom voor, maar bevatten enkel de zwarte sleutels. Dit dient om te testen, aangezien de constructor `RZWboom<Sleutel>(const std::vector<Sleutel> sleutels, const std::vector<Sleutel> zwarteSleutels)` eerst alle knopen zal toevoegen (en die zijn steeds rood), en daarna de juiste knopen zwart zal maken.

De `void tekenBoom(RZWboom<Sleutel>& boom, bool open_bestand)` functie zal de boom omvormen in .dot formaat, en zal deze automatisch converteren naar een .jpg ( **DIT VEREIST DAT HET DOT SCRIPT AANWEZIG IS IN UW PATH SYSTEEMVARIABELE** ) de bool open_bestand zal het bestand automatisch openen.

### rzwboom14.cpp
