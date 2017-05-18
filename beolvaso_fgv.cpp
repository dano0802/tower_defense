int beolvas(FILE *ptr_file, std::string *nev1, int *attr0, int *attr1, int *attr2, int *attr3, int *attr4)
{
    char buf[1000]; 
    const char s[2] = ";"; 
    char *token; 
    std::string nev;
    int attr[5];
    int i=-1;
              
    if (fgets(buf,1000, ptr_file)!=NULL) 
    {
        token = strtok(buf, s); 
		
      
        while( token != NULL ) 
        {
            if (i<0)
            {
                nev = token; 
            }
            else
            {
                attr[i] = atoi(token); 
            }
            i++;
            token = strtok(NULL, s);
        }
                        
        cout << endl << endl;
    }
    else
    {
        return -1; 
    }
    
   
    *nev1 = nev;
    *attr0=attr[0];
    *attr1=attr[1];
    *attr2=attr[2];
    *attr3=attr[3];
    *attr4=attr[4];
    
    return 0; 
}