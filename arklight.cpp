#include "arklight.h"



void cursore_manuale(int x, int y){
    HANDLE hConsole;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord_posizione = {x, y};
    posizione_cursore(coord_posizione);
}

void pulisci(){
    system("cls");
}

COORD posizione_attuale() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    return csbi.dwCursorPosition;
}

void cursore_alto(COORD* coord_posizione, int delta){
    HANDLE hConsole;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    coord_posizione->Y -= delta;
    posizione_cursore(*coord_posizione);
}

void cursore_basso(COORD* coord_posizione, int delta){
    HANDLE hConsole;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    coord_posizione->Y += delta;
    posizione_cursore(*coord_posizione);
}

void cursore_sinistra(COORD* coord_posizione, int delta){
    HANDLE hConsole;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    coord_posizione->X -= delta;
    posizione_cursore(*coord_posizione);
}

void cursore_destra(COORD* coord_posizione, int delta){
    HANDLE hConsole;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    coord_posizione->X += delta;
    posizione_cursore(*coord_posizione);
}

void posizione_cursore(COORD coord_posizione){
    HANDLE hConsole;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsole, coord_posizione);
}

void set_color(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void box_spazi(const char* text) {
    int AltoDestra = 187, AltoSinistra = 201, BassoDestra = 188, BassoSinistra = 200, LineaOrizz = 205, LineaVert = 186; // Codice ASCII per le linee
    int len = strlen(text); // Prendo la lunghezza del testo
    printf("%c", AltoSinistra); // Stampo l'angolo in alto a sinistra

    // Ciclo per stampare la lunghezza del box
    for (int i = 0; i < len + 4; i++) {
        printf("%c", LineaOrizz);
    }

    printf("%c\n", AltoDestra); // Stampo l'angolo in alto a destra
    printf("%c  ", LineaVert); // Stampo la seconda riga della prima colonna

    // Ciclo per stampare il numero corretto di spazi
    for (int i = 0; i < len; i++){
        printf(" ");
    }

    printf("  %c\n", LineaVert); // Stampo la seconda riga dell'ultima colonna
    printf("%c  %s  %c\n", LineaVert, text, LineaVert); // Stampo la riga con il testo e il contorno
    printf("%c  ", LineaVert); // Stampo la quarta riga della prima colonna

    // Ciclo per stampare il numero corretto di spazi
    for (int i = 0; i < len; i++){
        printf(" ");
    }

    printf("  %c\n", LineaVert); // Stampo la quarta riga dell'ultima colonna
    printf("%c", BassoSinistra); // Stampo l'angolo in basso a sinistra

    // Ciclo per stampare la lunghezza del box
    for (int i = 0; i < len + 4; i++){
        printf("%c", LineaOrizz);
    }
    printf("%c\n", BassoDestra); // Stampo l'angolo in basso a destra
    }


    void box(const char* text) {
    int AltoDestra = 187, AltoSinistra = 201, BassoDestra = 188, BassoSinistra = 200, LineaOrizz = 205, LineaVert = 186, IncrocioDestra = 185, IncrocioSinistra = 204; // Codice ASCII per le linee
    int len = strlen(text) + 8; // Prendo la lunghezza del testo + 8 per gli spazi e gli uguali
    printf("%c", AltoSinistra); // Stampo l'angolo in alto a sinistra

    // Ciclo per stampare la lunghezza del box
    for (int i = 0; i < len; i++) {
        printf("%c", LineaOrizz);
    }

    printf("%c\n", AltoDestra); // Stampo l'angolo in alto a destra
    printf("%c", LineaVert); // Stampo la seconda riga della prima colonna

    // Ciclo per stampare il numero corretto di spazi
    for (int i = 0; i < len; i++){
        printf(" ");
    }

    printf("%c\n", LineaVert); // Stampo la seconda riga dell'ultima colonna
    printf("%c%c%c%c %s %c%c%c%c\n", IncrocioSinistra, LineaOrizz, LineaOrizz, LineaOrizz, text, LineaOrizz, LineaOrizz, LineaOrizz, IncrocioDestra); // Stampo la riga con il testo e il contorno
    printf("%c", LineaVert); // Stampo la quarta riga della prima colonna

    // Ciclo per stampare il numero corretto di spazi
    for (int i = 0; i < len; i++){
        printf(" ");
    }

    printf("%c\n", LineaVert); // Stampo la quarta riga dell'ultima colonna
    printf("%c", BassoSinistra); // Stampo l'angolo in basso a sinistra

    // Ciclo per stampare la lunghezza del box
    for (int i = 0; i < len; i++){
        printf("%c", LineaOrizz);
    }
    printf("%c\n", BassoDestra); // Stampo l'angolo in basso a destra
}

void box_colore(const char* text, int color) {

    set_color(color); // Imposta il colore

    int AltoDestra = 187, AltoSinistra = 201, BassoDestra = 188, BassoSinistra = 200, LineaOrizz = 205, LineaVert = 186; // Codice ASCII per le linee
    int len = strlen(text); // Prendo la lunghezza del testo
    printf("%c", AltoSinistra); // Stampo l'angolo in alto a sinistra

    // Ciclo per stampare la lunghezza del box
    for (int i = 0; i < len + 4; i++) {
        printf("%c", LineaOrizz);
    }

    printf("%c\n", AltoDestra); // Stampo l'angolo in alto a destra
    printf("%c  ", LineaVert); // Stampo la seconda riga della prima colonna

    // Ciclo per stampare il numero corretto di spazi
    for (int i = 0; i < len; i++){
        printf(" ");
    }

    printf("  %c\n", LineaVert); // Stampo la seconda riga dell'ultima colonna
    printf("%c  ", LineaVert); // Stampo la riga con il testo e il contorno

    set_color(15); // Resetta il colore a bianco
    printf("%s", text); // Stampo la riga con il testo e il contorno

    set_color(color); // Imposta il colore
    printf("  %c\n", LineaVert);
    printf("%c  ", LineaVert); // Stampo la quarta riga della prima colonna

    // Ciclo per stampare il numero corretto di spazi
    for (int i = 0; i < len; i++){
        printf(" ");
    }

    printf("  %c\n", LineaVert); // Stampo la quarta riga dell'ultima colonna
    printf("%c", BassoSinistra); // Stampo l'angolo in basso a sinistra

    // Ciclo per stampare la lunghezza del box
    for (int i = 0; i < len + 4; i++){
        printf("%c", LineaOrizz);
    }
    printf("%c\n", BassoDestra); // Stampo l'angolo in basso a destra

    set_color(15); // Resetta il colore a bianco
}

void cornice(int margine_sinistro, int margine_superiore, int margine_destro, int margine_inferiore, char carattere){

    HANDLE hConsole;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    COORD coord_cornice = {margine_sinistro, margine_superiore};
    COORD coord_spazio;


    SetConsoleCursorPosition(hConsole, coord_cornice);

	for( int j = 0; j < margine_inferiore; j++){

    	for( int i = 0 ; i < margine_destro; i ++){

    		if (j == 0 || j == margine_inferiore -1){

    			putchar(carattere);

			} else if ( i == 0 || i == margine_destro - 1 ){

				putchar('*');

			} else {

                GetConsoleScreenBufferInfo(hConsole, &csbi);
                coord_spazio = csbi.dwCursorPosition;
                coord_spazio.X += 1;
                SetConsoleCursorPosition(hConsole, coord_spazio);
				//putchar(' ');

			}

		}

		coord_cornice.Y += 1;
		SetConsoleCursorPosition(hConsole, coord_cornice);

	}

    coord_cornice.Y += 5;
    SetConsoleCursorPosition(hConsole, coord_cornice);

}

void nascondi_cursore(){

    printf(CURSORE_INVISIBILE);

}

void mostra_cursore(){

    printf(CURSORE_VISIBILE);

}

void cursore(COORD posizione){

    HANDLE hConsole;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsole, posizione);

}

void funzioni_utili(){

    HANDLE hConsole;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

}

void scan(char *variabile) {

    if (fgets(variabile, strlen(variabile), stdin) != NULL) {

        variabile[strcspn(variabile, "\n")] = '\0';

    } else {

        printf("Errore nella lettura dell'input!\n");

    }

}

void matrici0(int righe, int colonne, char arr[righe][colonne]){

    for( int i = 0; i < righe; i++ ){

        for( int j = 0; j < colonne; j++ ){

            arr[i][j] = '.';

        }

    }

}

void array_rand(int lunghezza, int arr[lunghezza], int min, int max){

    srand(time(NULL));

    for ( int i = 0; i < lunghezza; i++){

        arr[i] = min + rand() % (max - min + 1);

    }

}

void matrici_rand(int righe, int colonne, char arr[righe][colonne], int min, int max){

    srand(time(NULL));

    for( int i = 0; i < righe; i++ ){

        for( int j = 0; j < colonne; j++ ){

            arr[i][j] = min + rand() % (max - min + 1);

        }

    }

}

void printarray(int lunghezza, int arr[lunghezza]){

    for ( int i = 0; i < lunghezza; i++){

        printf("%d\t", arr[i]);

    }

}

void print_matrici(int righe, int colonne, char arr[righe][colonne]){

    for( int i = 0; i < righe; i++ ){

        for( int j = 0; j < colonne; j++ ){

            printf("%c\t", arr[i][j]);

        }

        printf("\n");

    }

}

void print_matrici_special(int righe, int colonne, char arr[righe][colonne]){

    HANDLE hConsole;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    GetConsoleScreenBufferInfo(hConsole, &csbi);
    COORD coord_ciclo = csbi.dwCursorPosition;
    COORD coord_backup = csbi.dwCursorPosition;

    for( int i = 0; i < righe; i++ ){

        for( int j = 0; j < colonne; j++){

            coord_ciclo.X++;

            if (arr[i][j] == 0){
                //printf("0");
                SetConsoleCursorPosition(hConsole, coord_ciclo);
            } else {
                printf("%c", arr[i][j]);
            }

        }
        coord_ciclo.Y++;
        coord_ciclo.X = coord_backup.X;
        SetConsoleCursorPosition(hConsole, coord_ciclo);

    }

}

void cmd_grande(){

    HWND hwnd = GetConsoleWindow(); // Ottieni il manico della finestra del terminale
    ShowWindow(hwnd, SW_MAXIMIZE);

}

int is_sorted(int n, int arr[n]){

    for(int i = 0; i < n - 1; i++){
        if (arr[i] > arr[i + 1]){
            return 0;
        }
    }

    return 1;

}

void bubblesort(int n, int arr[n]){

    for(int i = 0; i < n - 1; i++){

        for(int j = 0; j < n -i - 1; j++){

            if(arr[j] > arr[j + 1]){

                arr[j] += arr[j+1] - (arr[j+1] = arr[j]);

            }

        }

    }

}

void selectionsort(int n, int arr[n]){

    for(int i = 0; i < n - 1; i++){

        int min = i;

        for(int j = i + 1; j < n; j++){

            if (arr[j] < arr[min]){

                min = j;

            }

        }

        arr[i] += arr[min] - (arr[min] = arr[i]);

    }

}

void mergesort(int n, int arr[n]){

    int l = n / 2;
    int r = n - l;
    int array1[l];
    int array2[r];

    for(int i = 0; i < l; i++){

        array1[i] = arr[i];

    }

    for( int i = l ; i < n; i++){

        array2[i - l] = arr[i];

    }

    if (n <= 1) return;
    mergesort(l, array1);
    mergesort(r, array2);


    for(int k = 0, i = 0, j = 0; i < l && j < r; k++){

        if (array1[i] < array2[j]){
            arr[k] = array1[i];
            i++;
            }
            else{
                arr[k] = array2[j];
                j++;
                }

    }

    int i= 0, j = 0, k = 0;

        // Copia gli elementi rimanenti di array1[], se ce ne sono
    while ( i < l) {
        arr[k] = array1[i];
        i++;
        k++;
    }

    // Copia gli elementi rimanenti di array2[], se ce ne sono
    while ( j < r) {
        arr[k] = array2[j];
        j++;
        k++;
    }


}

void cerca_numero(int n, int vett[n]){

    int numero_da_cercare, conta;
    printf("numero da cercare : ");
    scanf("%d", &numero_da_cercare);

    for(int i = 0 ; i < n; i++){

        if ( vett[i] == numero_da_cercare ){
            printf("il numero %d si trova alla posizione %d\n", numero_da_cercare, i + 1);
            conta++;
        }

    }

    printf("il numero %d %c stato trovato %d volte\n", numero_da_cercare, E, conta);

}


// RADIX SORT ARRAY


// Trova il massimo valore nell'array
int ottieni_massimo(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) max = arr[i];
    }
    return max;
}

// Ottieni la cifra nella posizione specificata
int ottieni_cifra(int numero, int exp) {
    return (numero / exp) % 10;
}
