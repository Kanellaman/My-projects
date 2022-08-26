#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MINNUM 10
#define MAXNUM 100
#define MAXK 5
#define COMPUTATIONS 21

int main()
{
    int n, count, i, temp, semiprimes, min, max, k_count, y, z, x, div;
    long curtime;
    semiprimes = 0;                    //Πλήθος ημι-πρώτων αριθμών
    k_count = 0;                       //Πλήθος k-πρώτων αριθμών
    for (n = MINNUM; n <= MAXNUM; n++) //Επανάληψη για την εύρεση του πλήθους των ημιπρώτων,του πλήθους όλων των k σχεδόν πρώτων(για 2<=k<=MAXK) και των ενδιαφέροντων ημιπρώτων που βρίσκονται στο διάστημα MINNUM-MAXNUM
    {
        count = 0;                      //Θεωρούμαι αρχικά ότι το πλήθος των ακέραιων διαιρετών του αριθμού n είναι 0
        temp = n;                       //Εκχώρηση του αριθμού n στην μεταβλτητή temp έτσι ώστε να γίνουν οι κατάλληλες πράξεις στην μεταβλητή temp για την εύρεση του πλήθους των ακέραιων διαιρετών του n χωρίς να αλλοιωθεί η τιμή του
        for (i = 2; i * i <= temp; i++) //Επανάληψη για την εύρεση του πλήθους των ακέραιων διαιρετών του n
        {
            while (temp % i == 0)
            {                    //Η επανάληψη γίνεται όσο ο αριθμός i είναι ακέραιος διαιρέτης του temp
                temp = temp / i; //Η temp λαμβάνει ως τιμή το πήλικο της διαίρεσης της με τον ακέραιο διαιρέτη της i
                count++;         //Το πλήθος τον ακέραιων διαιρετών του n αυξάνεται κατά ένα
                if (count == 1)
                {
                    min = i;    //Για την εύρεση των ενδιαφέροντων ημιπρώτων αρχικοποιούμε την μεταβλητή min με τον πρώτο ακέραιο διαιρέτη του n
                    max = temp; //Εφόσον εξετάζουμε ημιπρώτους αριθμούς οι δύο ακέραιοι διαιρέτες του συνδέονται με την σχέση max(ο μεγαλύτερος διαιρέτης)=temp/min(ο μικρότερος διαιρέτης)
                }
            }
        }
        if (temp != 1) //Σε αυτή την περίπτωση μετράμε τον τελευταίο διαιρέτη που έχει απομείνει
        {
            count++;
        }
        if (count == 2) //Αν ένας αριθμός είναι ημιπρώτος
        {
            semiprimes++;                                 //Αυξάνεται το πλήθος των ημιπρώτων κατά ένα
            if (min != max && (max - min) < (max * 0.01)) //Έλεγχος για το αν είναι ενδιαφέρον ημιπρώτος αριθμός
            {
                printf("%d * %d = %d is an interesting semiprime\n\n", min, max, n);
            }
        }
        if (count >= 2 && count <= MAXK) //Αν οι αριθμοί είναι k-πρώτοι(στο διάστημα του k)
        {
            k_count++;
        }
    }
    printf("Found %d %d-almost prime numbers\n", k_count, MAXK);
    printf("The semiprime numbers from %d till %d are %d\n", MINNUM, MAXNUM, semiprimes);
    curtime = time(NULL); //Παίρνει ως τιμή την ώρα unix τη στιγμή που τρέχει το πρόγραμμα
    srand((unsigned int)curtime);
    count = 0;
    for (i = 1; i < COMPUTATIONS; i++)
    {
        y = rand(); //Καλούμε την συνάρτηση rand για να μας δώσει μια ψευδοτυχαία τιμή
        z = rand(); //Την ξανακαλούμε για να μας δώσει την επόμενη ψευδοτυχαία τιμή
        x = ((y % 32768) + 1) * ((z % 32768) + 1) + 1;
        temp = x;
        count = 0;
        for (div = 2; div * div <= temp; div++)
        { //Έλεγχος για το τι k-πρώτος αριθμός είναι
            while (temp % div == 0)
            {
                temp = temp / div;
                count++; //Αυξάνει τον αριθμό των ακέραιων διαιρετών του x
            }
        }
        if (temp != 1) //Μετρά τον τελευταίο ακέραιο διαιρέτη του x
        {
            count++;
            temp = 1;
        }
        printf("The number %d is %d-almost prime\n", x, count);
    }
}
