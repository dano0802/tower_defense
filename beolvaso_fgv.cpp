int beolvas(FILE *ptr_file, std::string *nev1, int *attr0, int *attr1, int *attr2, int *attr3, int *attr4)
{
    char buf[1000]; //ebbe tesszük a beolvasott karakterláncot
    const char s[2] = ";"; //elválasztó karakter
    char *token; //részsztring eleje
    std::string nev;
    int attr[5];
    int i=-1;
              
    if (fgets(buf,1000, ptr_file)!=NULL) //beolvasunk egy sort ha nem null jöhet a kinyerés
    {
        token = strtok(buf, s); //első token
        
        /* többi token */
        while( token != NULL ) 
        {
            if (i<0)
            {
                nev = token; //név sztring átadása
            }
            else
            {
                attr[i] = atoi(token); //intre konvertálás
            }
            i++;
            token = strtok(NULL, s);
        }
                        
        cout << endl << endl;
    }
    else
    {
        return -1; //ha vége a fájlnak
    }
    
    /*átadjuk a külső változóknak az értéket*/
    *nev1 = nev;
    *attr0=attr[0];
    *attr1=attr[1];
    *attr2=attr[2];
    *attr3=attr[3];
    *attr4=attr[4];
    
    return 0; //ha megtörtént az adatok kinyerése
}
