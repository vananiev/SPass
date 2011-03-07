#ifndef _FILEH
#define _FILEH

#include <fstream.h>
#include <dir.h>

#define length 0x08000		//скачиваем байт раз

class File_Adr{
	public:
	char fdir[255];
	char fname[255];
	char fext[8];};
//*******************************************************************************************************
bool Copy_File(char * from, char * to,bool Del_First_File =false )
{
        unsigned char data[1024];
        ifstream in(from, ios::in| ios::binary);
        ofstream out(to, ios::out| ios::binary|ios::trunc);
	        if (!out || !in) return false;
        while(in){
                in.read(data,sizeof data);
                out.write(data, in.gcount());
                }
        if(Del_First_File)
                if(remove(from)) return false;
	return true;
}
//*******************************************************************************************************
int add_to_file(char *from, char *to, bool add=false,unsigned int seek_from=0,unsigned int len=-1,unsigned int seek_to=-1)
{
        char temp[MAXPATH];
        if(add && seek_to!=-1)	//вставка в середину файла
        	{
                //подготовим временный файл
        	strcpy(temp,to);
        	strcat(temp,"_");
        	rename(to,temp);
        	//копируем начало to-файла
        	add_to_file(temp,to,false,0,seek_to);
                }

        // open to stream
        ofstream out;
        if (add){
	        out.open(to, ios::out| ios::binary|ios::app);
                if (!out) return 2;}
                else{
                out.open(to, ios::out| ios::binary|ios::trunc);
                if (!out) return 2;}
        //open from
	ifstream in (from,ios::in|ios::binary);
	if (!in)  return -1;
	// copy
        in.seekg(seek_from,ios::beg);
        unsigned int cnt_byte=len;		//число скачанных байт
        char data[length];
	while(in && cnt_byte>0){
                if(cnt_byte>=length)
        		in.read(data,length);
                else
                        in.read(data,cnt_byte);
                unsigned int cnt = in.gcount();
                out.write(data,cnt);
                cnt_byte-=cnt;
                }
	in.close();
        out.close();
        if(add && seek_to!=-1)	//вставка в середину файла
        	{
        	//копируем конец to-файла
        	add_to_file(temp,to,true,seek_to);
        	if(remove(temp)) return 3;	//не удалось удалить временный файл
                }

        if(cnt_byte>0)
        	return 1;	//скачали не все тчо требовали, файл оказался меньше
        else
		return 0;
}
//*******************************************************************************************************
int add_to_file(char *from, char *to, char* pass,bool add=false,unsigned int seek_from=0,unsigned int len=-1,unsigned int seek_to=-1)
{
	char temp[MAXPATH];
        if(add && seek_to!=-1)	//вставка в середину файла
        	{
                //подготовим временный файл
        	strcpy(temp,to);
        	strcat(temp,"_");
        	rename(to,temp);
        	//копируем начало to-файла
        	add_to_file(temp,to,false,0,seek_to);
                }

        int passlen;
        ofstream out;
        union {
                unsigned int sum;
                unsigned char c[4];};
        sum=-34186*14373; //соль
        for(len=0;pass[len];len++)
        	{
        	//чтобы привязываться в пароле не только к символу, но и к местоположению
                //выполняем циклический сдвиг влево
                unsigned int sdvig;
                unsigned char t,g,j;
                sdvig = len%8;
                t = pass[len] & 255<<(8-sdvig);
                t = t>>(8-sdvig);
                g = pass[len]<<sdvig;
                j = g | t;
                for(int k=0;k<4;k++)
                	{
                	c[k] =c[k]^j; //sum *= pass[len];
                        }
                }
	// open to stream
        if (add){
	        out.open(to, ios::out| ios::binary|ios::app);
                if (!out) return 2;}
                else{
                out.open(to, ios::out| ios::binary|ios::trunc);
                if (!out) return 2;}
        //open from
	ifstream in (from,ios::in|ios::binary);
	if (!out)  return -1;
	// copy
        in.seekg(seek_from,ios::beg);
        unsigned int cnt_byte=len;		//число скачанных байт
        char data[length];
        unsigned int k=0;
	while(in && cnt_byte>0)
	{
        	if(cnt_byte>=length)
                	in.read(data,length);
                else
                	in.read(data,cnt_byte);
                unsigned int cnt=in.gcount();
                for(unsigned int i=0;i<cnt;i++,k++)
                	data[i]=data[i]^pass[k%passlen]^c[k%4];       //XOR
                out.write(data,cnt);
                cnt_byte-=cnt;
        }
	in.close();
        out.close();
        if(add && seek_to!=-1)	//вставка в середину файла
        	{
        	//копируем конец to-файла
        	add_to_file(temp,to,true,seek_to);
        	if(remove(temp)) return 3;	//не удалось удалить временный файл
                }
	if(cnt_byte>0)
        	return 1;	//скачали не все тчо требовали, файл оказался меньше
        else
		return 0;
}
//*******************************************************************************************************
//add==true seek==-1 добавляет в конец файла
int add_to_file_string(char* string, char *to, bool add=false,unsigned int seek=-1)
{
        if(add==false && seek==-1) seek=0;	//обнуляет файл и пишет с начала
	char temp[MAXPATH];
        if(add && seek!=-1)	//вставка в середину файла
        	{
                //подготовим временный файл
        	strcpy(temp,to);
        	strcat(temp,"_");
        	rename(to,temp);
        	//копируем начало to-файла
        	add_to_file(temp,to,false,0,seek);
                }

        ofstream out;
	// open to stream
        if (add)
	        out.open(to, ios::out| ios::binary|ios::app);
                else
                out.open(to, ios::out| ios::binary|ios::trunc);
	if (!out) return -1;
	// copy
	out.seekp(seek,ios::beg);
        unsigned int len;
        for(len=0;string[len];len++);
        out.write(string,len);
        out.close();
        if(add && seek!=-1)	//вставка в середину файла
        	{
        	//копируем конец to-файла
        	add_to_file(temp,to,true,seek);
        	if(remove(temp)) return 3;	//не удалось удалить временный файл
                }
	return 0;
}
//*******************************************************************************************************
//add==true seek==-1 добавляет в конец файла
int add_to_file_string(char* string, char *to, char* pass,bool add=false,unsigned int seek=-1)
{
	char temp[MAXPATH];
        if(add==false && seek==-1) seek=0;	//обнуляет файл и пишет с начала
        if(add && seek!=-1)	//вставка в середину файла
        	{
                //подготовим временный файл
        	strcpy(temp,to);
        	strcat(temp,"_");
        	rename(to,temp);
        	//копируем начало to-файла
        	add_to_file(temp,to,false,0,seek);
                }

        int len;
        union {
                unsigned int sum;
                unsigned char c[4];};
        sum=-34186*14373; //соль
        for(len=0;pass[len];len++)
        	{
        	//чтобы привязываться в пароле не только к символу, но и к местоположению
                //выполняем циклический сдвиг влево
                unsigned int sdvig;
                unsigned char t,g,j;
                sdvig = len%8;
                t = pass[len] & 255<<(8-sdvig);
                t = t>>(8-sdvig);
                g = pass[len]<<sdvig;
                j = g | t;
                for(int k=0;k<4;k++)
                	{
                	c[k] =c[k]^j; //sum *= pass[len];
                        }
                }
        ofstream out;
	// open to stream
        if (add)
	        out.open(to, ios::out| ios::binary|ios::app);
                else
                out.open(to, ios::out| ios::binary|ios::trunc);
	if (!out) return -1;
	// copy
	out.seekp(seek,ios::beg);
        int k;
        for(k=0;string[k];k++)
	{
                //XOR
                string[k]=string[k]^pass[k%len]^c[k%4];
        }
        out.write(string,k);
        out.close();
        if(add && seek!=-1)	//вставка в середину файла
        	{
        	//копируем конец to-файла
        	add_to_file(temp,to,true,seek);
        	if(remove(temp)) return 3;	//не удалось удалить временный файл
                }
	return 0;
}
//*******************************************************************************************************
int file_find_string(char* file,char* string,unsigned int from_pos=0)
{
        int len;
        for(len=0;string[len];len++);
        ifstream in(file, ios::in| ios::binary);
        in.seekg(from_pos,ios::beg);
        #define lenght 0x020000 //считается что lenght > len
        char buf[2][lenght];
        unsigned int pos=0,i=1,k,cnt=lenght,cnt_k;
        bool load = false;
        while(in){
                if(load)
                	{			//уже загружен следующий фрагмент ниже по коду
                	i=k;
                        cnt = cnt_k;
                        load = false;
                        }
                else{
                	if(cnt!=lenght || in.eof())		       	//просмотр файла закончен
                        	goto _ext;
                	if(i==0) i=1;                                   //загрузка нового фрагмента
                        else i=0;
        		in.read(buf[i],sizeof(buf[0]));
                	cnt=in.gcount();
                        }
                do
                	{
                    	if(buf[i][pos%lenght]==string[0])     //находим первый символ
                        	{
                                k=i;
                                unsigned int end = pos%lenght + len;
                                unsigned int j,s;
                                for(j=pos%lenght+1, s=1; j<end ;j++,s++)    	//проверка остальных имволов
                                	{
                                        if(j>=cnt && !load)			      	//подгружаем следующую часть файла
                                        	{
                                                if(cnt!=lenght || in.eof())		       	//просмотр файла закончен
                                                	goto _ext;
                                                if(k==0) k=1;
                                                else k=0;
                                                in.read(buf[k],sizeof(buf[0]));	//подгружаем
                				cnt_k=in.gcount();
                                                if(cnt_k==0)			//просмотр файла закончен
                                                	goto _ext;
                                                load=true;
                                                }
                                        if(buf[k][j%lenght] != string[s])
                                        	{
                                        	break;
                                                }
                                        }
                                if(j==end)	//проверка на равенство
                                	{in.close();return from_pos + pos;}
                                }
                    	pos++;
                	}while(pos%lenght < cnt && pos%lenght!=0);
                }
_ext:
        in.close();
        return -1;
}
//*******************************************************************************************************
int file_find_string(char* file,char* string,char* pass,unsigned int from_pos=0)
{
        char data;
        int len;
        int pass_len;
        union {
                unsigned int sum;
                unsigned char c[4];};
	sum=-34186*14373; //соль
        for(len=0;pass[len];len++)
        	{
        	//чтобы привязываться в пароле не только к символу, но и к местоположению
                //выполняем циклический сдвиг влево
                unsigned int sdvig;
                unsigned char t,g,j;
                sdvig = len%8;
                t = pass[len] & 255<<(8-sdvig);
                t = t>>(8-sdvig);
                g = pass[len]<<sdvig;
                j = g | t;
                for(int k=0;k<4;k++)
                	{
                	c[k] =c[k]^j; //sum *= pass[len];
                        }
                }
        for(len=0;string[len];len++)
                string[len]=string[len]^pass[len%pass_len]^c[len%4];
        
	return file_find_string(file,string,from_pos);
}
//*******************************************************************************************************
int get_from_file(char* file,char *string,int pos=0,unsigned int len=-1)
{
        char data;
        ifstream in(file, ios::in| ios::binary);
        in.seekg(pos,ios::beg);
        unsigned int i=0;
        in.read(string,len);
        string[in.gcount()]=0;//последний считанный символ - конец файла
        in.close();
        return 0;
}
//*******************************************************************************************************
int get_from_file(char* file,char *string,char* pass,unsigned int pos=0,unsigned int len=-1)
{
        int pass_len;
        union {
                unsigned int sum;
                unsigned char c[4];};
	sum=-34186*14373; //соль
        for(len=0;pass[len];len++)
        	{
        	//чтобы привязываться в пароле не только к символу, но и к местоположению
                //выполняем циклический сдвиг влево
                unsigned int sdvig;
                unsigned char t,g,j;
                sdvig = len%8;
                t = pass[len] & 255<<(8-sdvig);
                t = t>>(8-sdvig);
                g = pass[len]<<sdvig;
                j = g | t;
                for(int k=0;k<4;k++)
                	{
                	c[k] =c[k]^j; //sum *= pass[len];
                        }
                }
        get_from_file(file,string,pos,len);
        for(int i=0;string[i];i++)
                string[i]=string[i]^pass[i%pass_len]^c[i%4];
        return 0;
}
//*******************************************************************************************************
File_Adr file_adr_split(char full_name[255])
{
	int i,j,k,n;
	File_Adr file;
        //??????
        for(i=strlen(full_name)-1; i>=0 && full_name[i]!='\\'; i--);
        j=0;
        file.fdir[j] = 0;
        if(i!=-1)
                for (;j<i+1;j++)
                        file.fdir[j]=full_name[j];
        file.fdir[j]='\0';
        //??
        file.fname[0] = 0;
        for (j=i+1,k=0;full_name[j]!='.' && full_name[j];j++,k++)
                file.fname[k]=full_name[j];
        file.fname[k]='\0';
        //???
        k=0;
        file.fext[k] = 0;
        if(full_name[j])
                for (n=j+1,k=0;full_name[n];n++,k++)
                        file.fext[k]=full_name[n];
        file.fext[k]='\0';
	return file;
}

//*******************************************************************************************************
void file_adr_join(File_Adr file,char* name)
{
	int i,j,k,n;
        //??????
        for(i=0,k=0;file.fdir[i];i++,k++)
                    name[k]=file.fdir[i];
        //??
        for(i=0;file.fname[i];i++,k++)
                    name[k]=file.fname[i];
        name[k++]='.';
        //???
        for(i=0;file.fext[i];i++,k++)
                    name[k]=file.fext[i];
        name[k]=0;
}



//*******************************************************************************************************
static char f[1024][MAXPATH]; //полный путь к файлу
int seach_dir(char *path,bool (*func)(char*),bool SeachInSubdir=false)
{
	int done;
	const int dir_deep=32; //max DEEP dir
	struct ffblk file;
	int count=0;
	char dir[dir_deep][MAXPATH];
	int objcount=0;

	setdisk(toupper(path[0])-'A');
	if (chdir(path)) return 0;

	//seach file
	done=findfirst("*.*",&file,0);
	count=0;
	while(!done && count<dir_deep)
	{
		if (file.ff_name[0]=='.')
		{
			done=findnext(&file);
			continue;
                }
		//make dir adr
		strcpy(f[count],path);
		if(f[count][strlen(dir[count])-1]!='\\')
                	strcat(f[count],"\\");
		strcat(f[count],file.ff_name);
//call func
		if((*func)(f[count])) return objcount+=count;
		done=findnext(&file);
		count++;
	}
        
        //seach directory

	done=findfirst("*.",&file,17);
	count=0;
	while(!done && count<dir_deep)
	{
		if (file.ff_name[0]=='.')
		{
			done=findnext(&file);
			continue;
                }
		//make dir adr
		strcpy(dir[count],path);
		if(dir[count][strlen(dir[count])-1]!='\\')
                	strcat(dir[count],"\\");
		strcat(dir[count],file.ff_name);
//call func
		if((*func)(dir[count])) return objcount+=count;
		done=findnext(&file);
		count++;
	}
        objcount+=count;
        //seach in found directoryes
        if(SeachInSubdir)
	        for(int i=0; i<count; i++)  objcount+=seach_dir(dir[i],func,SeachInSubdir);
	
	//number of subdirs
	return objcount;
}//seach_dir
//*******************************************************************************************************
bool split_str(char *Str,  char* divider,  char* res, int NumOfStr = 2, int LenOfStr = 256)
{
        int n=0;
        int i=0;
        int j=0;
        bool more = true;
        bool ans = true;
        while(Str[n]){
                        if(more && ((unsigned char) Str[n] != (unsigned char)divider[0]))
                                    {*(res+i*LenOfStr+j) = Str[n];
                                    j++;
                                    n++;
                                    if(j >= LenOfStr) {
                                                ans = false;
                                                more = false;}
                                    }
                        else{
                                if(more == false)
                                        {more = true;
                                        j=LenOfStr;}
                                *(res+i*LenOfStr+j) = 0;
                                j=0;
                                i++;
                                if(i >= NumOfStr) return false;
                                for(int m=0; (unsigned char) Str[n] == (unsigned char)divider[m];m++,n++)
                                        if(Str[n] == 0) return true;
                                }
                }
        return ans; //false - если строка обрезана, не помещаясь в LenOfStr, или не хватило строк.
}
//*******************************************************************************************************
char* DosToAnsi(unsigned char * s)
{
        for(int i=0;s[i];i++)
                {if(s[i]>=0x80 && s[i]<=0xAF) //АБВ-ЭЮЯ,абв-мноп
                        s[i]+=0x40;
                else if(s[i]>=0xE0 && s[i]<=0xEF) //рст-эюя
                        s[i]+=0x10;
                else if(s[i] == 0xF0) 			//Ё
                        s[i] = 0xA8;
                else if(s[i] == 0xF1) 			//ё
			s[i] = 0xB8;
		else if(s[i] == 0xFC) 			//№
			s[i] = 0xB9;
		else if(s[i] == 0xFF)                   //пробел
                        s[i] = 0x20;
                }
        return s;
}
//*******************************************************************************************************
char* AnsiToDos(unsigned char * s)
{
        for(int i=0;s[i];i++)
                {if(s[i]>=0xC0 && s[i]<=0xEF) //АБВ-ЭЮЯ,абв-мноп
                        s[i]-=0x40;
                else if(s[i]>=0xF0 && s[i]<=0xFF) //рст-эюя
                        s[i]-=0x10;
                else if(s[i] == 0xA8) 			//Ё
			s[i] = 0xF0;
                else if(s[i] == 0xB8) 			//ё
			s[i] = 0xF1;
		else if(s[i] == 0xB9) 			//№
			s[i] = 0xFC;
		
		}
        return s;
}
//*******************************************************************************************************
void seach_drv(int drv[25], bool (*func)(int), int DRIVE_TYPE=3)
{
   /*	#define DRIVE_UNKNOWN     0
	#define DRIVE_NO_ROOT_DIR 1
	#define DRIVE_REMOVABLE   2
	#define DRIVE_FIXED       3
	#define DRIVE_REMOTE      4
	#define DRIVE_CDROM       5
	#define DRIVE_RAMDISK     6
   */
   int save;
   int disks=0;
   char d[2];
   unsigned int errmode;

   for(int j=0;j<25;j++)
	drv[j]=-1;
   /* save original drive and get numbers of logical disk */
   save = getdisk();

   /* the drive letters available */
   errmode = SetErrorMode ( SEM_FAILCRITICALERRORS );
   for (int disk = 0;disk < 25;++disk)
   {
      setdisk(disk);
      if (disk == getdisk())
      {
        d[0]=getdisk()+'A';
        d[1]=':';
        if (GetDriveType(d)==DRIVE_TYPE)
        {
                drv[disks]=disk;
                disks++;
        }
      }
   }
   
   //call func
   for(int disk=0;disk<disks;disk++)
   	if((*func)(drv[disk])) return;
   

   SetErrorMode ( errmode );
   setdisk(save);

   return;
}
//*******************************************************************************************************
#endif