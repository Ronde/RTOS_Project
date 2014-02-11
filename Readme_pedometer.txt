Per confrontare il numero di passi è stata creata una funzione 

Pedometer::compareSteps(int otherSteps). 

per poterla usare è necessario ottenere un istanza di pedometer, creando nella classe che la userà un puntatore ad un oggetto pedometer

Pedometer* pedometer;

in seguito si dovrà richiedere una nuova istanza di pedometer con la funzione

pedometer = Pedometer::getInstance();

(come esempio vedere statistics.cpp)