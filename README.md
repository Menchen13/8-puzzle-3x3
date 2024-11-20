# 8-puzzle: Ein Program zum lösen des 8-Puzzle-Problems.
Dieses Programm ist als Prüfungsleistung für meinen Kurs "Einführung Artificial Intelligence" an der Leibiz-FH erstellt worden.
Es kann mithilfe des CMakeLists.txt Files gebaut werden und -h,--help gibt eine Nutzungsanleitung aus.

Zum Parsen der command line arguments wird [CLI11](https://github.com/CLIUtils/CLI11?tab=readme-ov-file#license) verwendet.

## Spezifikation
Ich habe mich für die Spezielle Defintion des 8-Puzzle-Problems dieser [Seite](https://www.8puzzle.com/8_puzzle_problem.html) entschieden und
verwende daher diese Zielzustände:
![Goal States](image/Goal_States.png)

# Fragen des Dozenten
1. **Wie ist ein Node modelliert?**

    Eine Node ist als Klasse modelliert. Dies ermöglicht es mir wichtige Attribute wie den State(fieldArray), Schrittzähler(movecount) und die Kosten(cost) zu kapseln und über Methoden der Klasse zu ändern/verwenden. Alle Attribute und Methoden Deklarationen können in der node.h Datei gefunden werden. Die dazugehörigen Implementirungen sind in der node.cpp Datei angesammelt.

2. **Wie werden die Successor Nodes erzeugt?**

    Die Routine zur erzeugung von Successor Nodes ist in der solver.h Datei auf Zeilen 63-83 zu finden. Um alle möglichen Successor Nodes zu erzeugen wird über alle möglichen Zugrichtung des leeren Feldes iteriert und geprüft ob der Zug "legal" ist. Ist der Zug erlaubt wird als Basis für die Successor Node die derzeit untersuchte Node kopiert. Es wird das parent Attribut der Successor node gesetzt und dannach der Zug, zum abändern des States, ausgeführt. Abschließend werden die Kosten der Successor Node berechnet, in dem cost Attribut festgehalten und die Node der Priority-Queue hinzugefügt.
    

3. **Vergleich Verwenden A-star vs. Greedy**

    Ich habe für beide Suchstrategien einen Komparator für die Priority-Queue geschrieben. Diese sind in solver.h in Zeilen 7-21 zu finden. Die verwendete Suchstrategie kann mithilfe der "-a" und "-g" command line flags ausgewählt werden. Wird keine der Flagen verwendet defaultet das Programm zu der A* Suchstrategie, da in meinen Tests(Windows 11 mit 16GB RAM) die Greedy Suchstrategie, mit den verfügbaren Ressourcen, nicht immer zu einem Ergebniss kam(Der PC gebrickt wurde). 

4. **Welche Heurisitik verwenden Sie und wo kann dies im Code gefunden werden? (kurze Erklärung)?**

    Ich verwende zum Brechnen der Kosten einer Node die Manhattan Distanz.
    Diese Kosten-Berechnung ist für beide Zielzustände seperat implementiert und kann in der node.cpp Datei in Zeilen 30-50 gefunden werden.
    Die Funktionen funktionieren im Kern gleich aber verwenden verschiedene Goal_States zur Berechnung. Zuerst wird die Index-Distanz eines Elements zu seiner Ziel-Position berechnet. Diese Index-Distanz wird dann durch drei geteilt und abgerundet um die benötigten vertikalten Schritte des Elements zu seiner Ziel-Position zu berechnen. Um die benötigten horizontalen Schritte eines Elements zu seiner Ziel-Position zu erhalten wird die Index-Distanz mod 3 gerechnet. Diese Beiden Werte, horzontale und vertikale benötigte Schritt-Anzahl werden addiert und bilden die Kosten des einzelnen Elementes.
    Um die Kosten des gesamten Feldes(der Node) zu erhalten werden also alle Element-Kosten addiert, was mithilfe der for schleife realisiert wird.

5. **Wie ist ihre Goal() Funktion modelliert?**

    Meine Goal() Function, welche prüft ob das Probelm gelöst würde, ist in der solver.h Datei in Zeilen 55-61 zu finden. Sie prüft ob die derzeit untersuchte Node einen Zielzustand enthält(cost == 0), ist dies der Fall, wurde eine Lösung für das 8-Puzzle-Problem gefunden und der Pfad zu dieser Node wird ausgegeben. Es ist wichtig anzumerken, dass die derzeit untersuchte Node immer die, nach Suchstrategie definiert, günstigste ist, da sie vom Anfang der, mit der Suchstrategie priorisierten, Priority-Queue genommen wird.
    Somit kann gewährleistet werden, dass z.B. A* immer die optimalste Lösung findet.
