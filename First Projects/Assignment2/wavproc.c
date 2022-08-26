// Tested for all modes(1,2,3,4,5,6,7)
// !!!Before run select MODE!!!
#include <stdio.h>
#define MODE 1
#include <math.h>
void Putchar(int temp, int n) //Συνάρτηση για την αποθήκευση της τιμής temp σε n byte με το πρότυπο little endian
{
    int w;
    putchar(temp); //Αποθηκεύονται τα 8 πρώτα bits από τον αιρθμό (μετρώντας από δεξία προς τα αριστερά)
    for (w = 1; w <= n - 1; w++)
    {
        temp = temp >> 8; //Ολίσθηση του αριθμού προς τα δεξιά για να αποθηκεύσουμε τα επόμενα 8 bits που θέλουμε
        putchar(temp);
    }
}
void mod(int temp, int n) //Συνάρτηση για τον πολλαπλασιασμό ή την διαίρεση του αριθμού temp n bytes ο οποίος ύστερα αποθηκεύει στο νέο αρχείο
{
    if (MODE == 2 || MODE == 4 || MODE == 5)
        temp = temp >> 1; //Διαίρεση του αριθμού με το δύο
    else if (MODE == 3)
        temp = temp << 1; //Πολλαπλασιασμός του αιρθμού με το δύο
    Putchar(temp, n);
}
void mysound(int dur, int sr, double fm, double fc, double mi, double mv) //Συνάρτηση για την παραγωγή του δικού μας ήχου με τις κατάλληλες παραμέτρους
{
    double f, t, k = 0.0;
    while (k != dur * sr) //Οι χρονικές στιγμές που θα έχει το νέο αρχείο θα είναι sr*dur και για αυτό προκύπτει η συνθήκη αυτή
    {
        t = k / sr; //Κάθε χρονική στιγμή στην οποία γράφονται δεδομένα του ήχου
        f = mv * sin(2 * M_PI * fc * t - mi * sin(2 * M_PI * fm * t));
        Putchar(f, 2);
        k = k + 1.0; //Μετρητής χρονικών στιγμών
    }
}
int main(void)
{
    signed short w;
    int ch, i = 0, temp = 0, k = 0, mo_st = 0, sa_ra, by_sec, bl_al, x = 0, size = 0, filesize, y, p = 0, h, size_for, wave_for, bits_sa, filesize2, F, H, dur, sr;
    double fm, fc, mi, mv;
    if (MODE != 7) //Σε περίπτωση mode 1,2,3,4,5,6
    {
        printf("Reading from input file...\n");
        while ((ch = getchar()) != EOF)
        {
            if (MODE == 2 || MODE == 3) // MODE 2,3
            {
                if (i > 31 || i < 24)
                {
                    putchar(ch); //Δεδομ΄΄ενα των οποίων η τιμή θέλουμε να επιστρέψουμε αυτούσια στην έξοδο καθώς δεν αλλάζουν
                }
            }
            if (MODE == 4 || MODE == 5)
            {
                if (MODE == 4)
                {
                    F = 44; //Για το αριστερό κανάλι ήχου για αρχείο που τα δεδομένα ήχου αποθηκεύονται ανά δυο bytes
                    H = 0;  //Για το αριστερό κανάλι ήχου για αρχείο που τα δεδομένα ήχου αποθηκε΄θονται ανά ενα bye
                }
                else
                {
                    F = 46; //Για το δεξιά κανάλι ήχου για αρχείο που τα δεδομένα ήχου αποθηκεύονται ανά δυο bytes
                    H = 1;  //Για το δεξιά κανάλι ήχου για αρχείο που τα δεδομένα ήχου αποθηκε΄θονται ανά ενα bye
                }
                if (i == 44)
                {
                    putchar('R');
                    putchar('I');
                    putchar('F');
                    putchar('F');
                    if (mo_st == 2)
                    {
                        temp = size / 2;
                        filesize2 = filesize - temp; //Υπολογισμός του μεγέθους του νέου αρχείου αφαιρώντας το πλήθος των bytes του καναλιού που δεν θα γράψουμε στο νέο αρχείο
                    }
                    else
                        filesize2 = filesize; //Αν το αρχείο είναι ήδη μονοφωνικό το μέγεθος του παραμένει το ίδιο
                    Putchar(filesize2, 4);
                    putchar('W');
                    putchar('A');
                    putchar('V');
                    putchar('E');
                    putchar('f');
                    putchar('m');
                    putchar('t');
                    putchar(' ');
                    Putchar(size_for, 4);
                    Putchar(wave_for, 2);
                    putchar(1); //Για την παραγωγή μονοφωνικού αρχείου (είτε είναι ήδη είτε δεν είναι)
                    putchar(0);
                    Putchar(sa_ra, 4);
                    if (mo_st == 2)
                    {
                        mod(by_sec, 4);
                        mod(bl_al, 2);
                    }
                    else
                    {
                        Putchar(by_sec, 4);
                        Putchar(bl_al, 2);
                    }
                    Putchar(bits_sa, 2);
                    putchar('d');
                    putchar('a');
                    putchar('t');
                    putchar('a');
                    Putchar(temp, 4);
                }
                if (mo_st == 2 && i >= 44)
                {
                    if (x <= size) //Η συνθήκη αυτή εξασφαλίζει ΄ότι θα μεταφέρουμε ατούσια στο νέο αρχείο τα άλλα τμήματα που προβλέπονται για την κατηγορία WAVE
                    {
                        if (bits_sa == 16)
                        {
                            if ((i == F + p * 2) || (i == F + p * 2 + 1)) //Συνθήκη ώστε να γράφουμε στο αρχείο μόνο το κανάλι που μας υποδεικνύει το F
                            {
                                putchar(ch);
                            }
                            if (i == F + p * 2 + 1)
                            {
                                p += 2; //Βήμα το οποία αυξάνεται κατά δυο για να μην υπολογιστεί το ανεπιθύμητο κανάλι
                            }
                        }
                        else if (bits_sa == 8 && i >= 44)
                        {

                            if (i % 2 == H) //Συνθήκη ώστε να γράφουμε στο αρχείο μόνο το κανάλι που μας υποδεικνύει το H
                            {
                                putchar(ch);
                            }
                        }
                    }
                    else
                        putchar(ch);
                }
                else if (mo_st == 1 && i >= 44) //Συνθήκη που εξασφαλίζει την αυτούσια μεταφορά των δεδομένων στο νέο αρχείο σε περίπτωση που το αρχείο είναι ήδη μονοφωνικό
                    putchar(ch);
            }
            if (MODE == 6)
            {
                if (i <= 43)
                    putchar(ch); //Δεδομ΄΄ενα των οποίων η τιμή θέλουμε να επιστρέψουμε αυτούσια στην έφοδο καθώς δεν αλλάζουν
            }
            if ((i >= 4 && i < 8) || (i >= 16 && i < 20) || (i >= 20 && i < 22) || (i >= 22 && i < 24) || (i >= 24 && i < 28) || (i >= 28 && i < 32) || (i >= 32 && i < 34) || (i >= 34 && i < 36) || (i >= 40 && i < 44) || i >= 44) //Αποθήκευση του αριθμού σε μια μεταβητή -temp- σύμφωνα με το πρότυπο αποθήκευσης little endian
            {
                ch = ch << 8 * k;
                temp = temp + ch;
                k++;
            }
            else //Ακολουθούν συνθήκες για τον εντοπισμό τυχών λαθών στα αρχεία που δέχονται σαν είσοδο
            {
                h = 1;                                                                                   //Μεταβλητή για τoν εντοπισμό τερματισμού της επανάληψης λόγω λάθους-error
                if ((i == 0 && ch != 'R') || (i == 1 && ch != 'I') || ((i == 2 || i == 3) && ch != 'F')) //Για το riff
                {
                    fprintf(stderr, "Error! \"RIFF\" not found\n");
                }
                else if ((i == 8 && ch != 'W') || (i == 9 && ch != 'A') || (i == 10 && ch != 'V') || (i == 11 && ch != 'E')) //Για το wave
                {
                    fprintf(stderr, "Error! \"WAVE\" not found\n");
                }
                else if ((i == 12 && ch != 'f') || (i == 13 && ch != 'm') || (i == 14 && ch != 't')) //Για το fmt
                {
                    fprintf(stderr, "Error! \"fmt\" not found\n");
                }
                else if ((i == 36 && ch != 'd') || ((i == 37 || i == 39) && ch != 'a') || (i == 38 && ch != 't')) //Για το data
                {
                    fprintf(stderr, "Error! \"data\" not found\n");
                }
                else
                {
                    h = 0; //Αν δεν υπάρχει λάθος(που αφορά τις παραπάνω συνθήκες) εκτελείται η πράξη αυτή
                }
                if (h == 1)
                {
                    break; //Αν το h παραμένει 1 και δε γίνει 0 αυτο σημαίνει οτι υπήρξε κάποιο σφάλμα και πρέπει να διακοπεί το πρόγραμμα
                }
            }
            if (MODE == 6)
            {
                if (i > 43)
                {
                    if (bits_sa == 8)
                    {
                        temp = temp / 8; //Μείωση την έντασης στο 1/8 της
                        putchar(temp);
                        temp = 0;
                        k = 0;
                    }
                    else if (bits_sa == 16)
                    {
                        if (i % 2 == 1)
                        {
                            w = temp; //Αποθήκεθση της μεταβλητής σε signed μεταβλητή για την σωστή διαίρεση της δια 8 και την αποφυγή λογικού λάθους
                            w = w / 8;
                            putchar(w);
                            w = w >> 8;
                            putchar(w);
                            temp = 0;
                            k = 0;
                        }
                    }
                }
            }
            if (i == 7)
            {
                fprintf(stderr, "size of file: %d\n", temp);
                filesize = temp;
                k = 0;
                temp = 0;
            }
            else if (i == 19) // size of format chunk
            {
                fprintf(stderr, "size of format chunk:%d\n", temp);
                k = 0;
                size_for = temp;
                if (temp != 16)
                {
                    fprintf(stderr, "Error! size of format chunck should be 16\n");
                    h = 1;
                    break;
                }
                temp = 0;
            }
            else if (i == 21) // wave format
            {
                fprintf(stderr, "WAVE type format:%d\n", temp);
                wave_for = temp;
                if (temp != 1)
                {
                    fprintf(stderr, "Error! WAVE type format should be 1\n");
                    h = 1;
                    break;
                }
                k = 0;
                temp = 0;
            }
            else if (i == 23) // mono stereo
            {
                fprintf(stderr, "mono/stereo:%d\n", temp);
                k = 0;
                mo_st = temp;
                if (mo_st != 1 && mo_st != 2)
                {
                    fprintf(stderr, "Error! mono/stereo should be 1 or 2\n");
                    h = 1;
                    break;
                }
                temp = 0;
            }
            else if (i == 27)
            {
                fprintf(stderr, "sample rate:%d\n", temp);
                sa_ra = temp;
                if (MODE == 2 || MODE == 3)
                    mod(temp, 4); //Μετατροπή του sample rate για το αντίστοιχο mode
                k = 0;
                temp = 0;
            }
            else if (i == 31)
            {
                fprintf(stderr, "bytes/sec:%d\n", temp);
                by_sec = temp;
                if (MODE == 2 || MODE == 3)
                    mod(temp, 4); //Μετατροπή των bytes per second για το αντίστοιχο mode
                temp = 0;
                k = 0;
            }
            else if (i == 33)
            {
                fprintf(stderr, "block alignment:%d\n", temp);
                bl_al = temp;
                if (by_sec != (sa_ra * bl_al))
                {
                    fprintf(stderr, "Error! bytes/second should be sample rate x block alignment\n");
                    h = 1;
                    break;
                }
                k = 0;
                temp = 0;
            }
            else if (i == 35)
            {
                fprintf(stderr, "bits/sample:%d\n", temp);
                bits_sa = temp;
                if (bl_al != (temp / 8 * mo_st))
                {
                    if (temp == 16 || temp == 8)
                    {
                        fprintf(stderr, "Error! block alignment should be bits per sample / 8 x mono/stereo\n");
                    }
                    else
                    {
                        fprintf(stderr, "Error! bits/sample should be 8 or 16\n");
                    }
                    h = 1;
                    break;
                }
                k = 0;
                temp = 0;
            }
            else if (i == 43)
            {
                fprintf(stderr, "size of data chunk:%d\n", temp);
                k = 0;
                size = temp;
                temp = 0;
            }
            if (i > 43)
            {
                x++;
            }
            i++;
        }
        if (h == 0) //Αυτό υποδεικν΄υει ΄ότι δεν υπήρξε κάποιο σφάλμα αλλιώς θα ήταν 1
        {
            if (x < size)
            {
                fprintf(stderr, "Error! insufficient data\n");
            }
            else if (x > size)
            {
                y = 36 + x;
                if (y != filesize) // 36 είναι τα bytes απο το SizeOfFile μέχρι και το SizeOfData και τα οποία πρέπει να προστεθούν με το x που μετράει τα bytes απο το SizseOfData και μετά ώστε να υπολογίσουμε το μέγεθος του αρχείο με αυτό που έχει αποθηκευτεί στο filesize
                {
                    fprintf(stderr, "Error! bad file size\n");
                }
            }
        }
    }
    else
    {
        h = 0;
        dur = 3;
        sr = 44100;
        fm = 2.0;
        fc = 1500.0;
        mi = 100.0;
        mv = 30000.0;
        mo_st = 1;
        bits_sa = 16;
        size_for = 16;
        wave_for = 1;
        bl_al = bits_sa / 8 * mo_st;
        size = sr * (bits_sa / 8) * dur;
        by_sec = sr * bl_al;
        filesize = size + 36;
        putchar('R');
        putchar('I');
        putchar('F');
        putchar('F');
        Putchar(filesize, 4);
        putchar('W');
        putchar('A');
        putchar('V');
        putchar('E');
        putchar('f');
        putchar('m');
        putchar('t');
        putchar(' ');
        Putchar(size_for, 4);
        Putchar(wave_for, 2);
        Putchar(mo_st, 2);
        Putchar(sr, 4);
        Putchar(by_sec, 4);
        Putchar(bl_al, 2);
        Putchar(bits_sa, 2);
        putchar('d');
        putchar('a');
        putchar('t');
        putchar('a');
        Putchar(size, 4);
        mysound(dur, sr, fm, fc, mi, mv);
    }
    return 0;
}
