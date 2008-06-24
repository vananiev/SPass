#include "registry.hpp"
const len=256;
const user_len=3;
class f
        {
        char pass[len];
        char parol[len];
        char user[user_len];
        char user_name[32];
        int schuser;
        public:
        char result[16];
        f();
        void clear();
        void read_data();
        void brain(char c);
        };
//--------------------------------------------------------------------------        
void f::read_data()
{       TRegistry *reg = new TRegistry(KEY_ALL_ACCESS);
        char* a="SOFTWARE\\user_config\\";
        if (reg)
        {
                reg->RootKey = HKEY_LOCAL_MACHINE;
                user[user_len]=0;
                a[21]=0;
                reg->OpenKeyReadOnly(strcat(a,user));
                if (reg->ValueExists("name"));
                if (reg->ValueExists("name"))
                        strcpy(user_name,reg->ReadString("name").c_str());
                if (reg->ValueExists("pass"))
                {
                        strcpy(parol,reg->ReadString("pass").c_str());
                        schuser=0;
                }
                reg->CloseKey();
        }
        delete reg;
}
//--------------------------------------------------------------------------
void f::brain(char c)
{
        if(c=='\r')
                {
                clear();
                return;
                }
        if(schuser)
                {
                if (strlen(user)<user_len)
                        user[strlen(user)]=c;
                        else
                        {
                        for(int i=1;i<user_len;i++)
                                user[i-1]=user[i];
                        user[user_len-1]=c;
                        user[user_len]=0;
                        }
                }
                else
                pass[strlen(pass)]=c;
        if(schuser && user[user_len-1]!=0)
                  read_data();
        if (!strcmp(pass,parol) &&  !schuser)
                {
                char *a="Идентификация пройдена успешно. Здравствуйте ";
                a[45]=0;
                MessageBox(NULL,strcat(a,user_name),"Вход разрешен" ,NULL);
                if(user_name=="guest")
                        result="guest";
                        else
                        result="administrator";
                }
}
//--------------------------------------------------------------------------
f::f()
{
        clear();
}
//--------------------------------------------------------------------------
void f::clear()
{
        for(int i=0;i<len;i++)
                {
                pass[i]=0;
                parol[i]=0;
                }
        for (int i=0;i<user_len;i++)
                user[i]=0;
        for (int i=0;i<32;i++)
                user_name[i]=0;
        schuser=1;
        result=0;
}
