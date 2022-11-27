#include <bits/stdc++.h> 
#define max 1000
using namespace std;
int levenshtein(const char *s, const char *t);
char *strlwr(char *str);
int sum(int count[max],int num1);
double dotprod(char words1[max][50],char words2[max][50],int num1,int num2,int count1[max],int count2[max]);
int occurences(FILE *fp,int count[max],char words[max][50]);
int min2(int a,int b);
int min3(int a,int b,int c);
int max2(int a,int b);
int main() 
{
    int inp;
    cout<<"Welcome to Plagiarism Checker by Vivan Desai"<<endl;
    cout<<"Please enter the following commands for plagiarism check"<<endl;
    cout<<"1- If you wannt to check source code file Press ==> 1"<<endl;
    cout<<"2- If you wannt to check plain text document file Press ==> 0"<<endl;
    cout<<"Code ==> 1 | Text Doc ==> 0"<<endl;
    cout<<"Please enter your Digit:"<<endl;
    cin>>inp;
    if(inp==1){
        char filename1[100],filename2[100];
        cout<<"Enter file filename1: ";
        cin>>filename1;
        cout<<"Enter file filename2: ";
        cin>>filename2;
        string str1;
        string str2;
        string buffer;
        ifstream input1(filename1);
        while (getline(input1, buffer))
            str1 += (buffer + '\n');
        ifstream input2(filename2);
        while (getline(input2, buffer))
            str2 += (buffer + '\n');
        float maximum=max2(str1.size(),str2.size());
        float leven=levenshtein(str1.c_str(),str2.c_str())/maximum;
        float plag=(1-leven)*100;
        cout<<plag<<"%"<<endl;
        if(plag>=30&&plag<=100)
	    {
	    	cout<<"plagiarised"<<endl;
	    }
	    else
	    {
	    	cout<<"not plagiarised"<<endl;
	    }
        }
    else
    {
        FILE *fp1,*fp2;
        const double PI =  3.1415926;
        char path1[100],path2[100];
        char words1[max][50],words2[max][50];
        int  count1[max],count2[max];
        cout<<"Please enter the file path for File #1: ";
        cin>>path1;
        cout<<"Please enter the file path for File #2:";
        cin>>path2;
        fp1=fopen(path1, "r"); 
        fp2=fopen(path2, "r"); 
        if (fp1 == NULL||fp2 == NULL){
            cout<<"Entered file is empty!\n";
            exit(EXIT_FAILURE);
        }
        int num1=occurences(fp1,count1,words1);
        fclose(fp1);
        /*cout<<"\n\n\n\n";*/
        int num2=occurences(fp2,count2,words2);
        fclose(fp2);
        double mod1=sqrt(sum(count1,num1));
        double mod2=sqrt(sum(count2,num2));
        //cout<<"mod1="<<mod1<<"\nmod2="<<mod2;
        double dotsum=dotprod(words1,words2,num1,num2,count1,count2);
        //cout<<"dotprod="<<dotsum<<endl; 
        double plag=acos(dotsum/(mod1*mod2))*180/PI;
        cout<<"cosine angle is in degrees: "<<plag<<endl;
        if(plag>=0&&plag<=45)
	    {
	    	cout<<"plagiarised"<<endl;
	    }
	    else
	    {
	    	cout<<"not plagiarised"<<endl;
	    }
    }	
}
int max2(int a,int b)
{
	return a>b?a:b;
}
int min2 (int a,int b)
{
    return a<b?a:b;
}

int min3 (int a,int b,int c)
{
    return min2(a,min2(b,c));
}
char *strlwr(char *str)
{
  char *p=(char *)str;
  while (*p)
  {
     *p=tolower((char)*p);
      p++;
  }
  return str;
}
double dotprod(char words1[max][50],char words2[max][50],int num1,int num2,int count1[max],int count2[max])
{
    int i,j;
    double s=0;
    for(i=0;i<num1;i++)
    {
        for(j=0;j<num2;j++)
        {
            if(strcmp(words2[j],words1[i])==0)
            {
                s=s+count1[i]*count2[j];
                break;
            }
        }
    }
    return s;
}
int sum(int count[max],int num1)
{
    int i,s=0;
    for(i=0;i<num1;i++)
    {
        s=s+pow(count[i],2);
    }
    return s;
}
int occurences(FILE *fp,int count[max],char words[max][50])
{
    char word[50];
    int i,len,index,uniq,j;
    for (i=0;i<max;i++)
        count[i]=0;
    index = 0;
    while (fscanf(fp,"%s",word)!=EOF)
    {
        for(j=0,i=0;i<strlen(word);i++)
        {
            if(isalnum(word[i]))
            {
                word[j]=word[i];
                j++;
            }
        }
        if(j!=0){
            word[j]='\0';
            strlwr(word);
            len=strlen(word);
            uniq=1;
            for(i=0;i<index;i++)
            {
                if(strcmp(words[i],word)==0)
                {
                    uniq=0;
                    break;
                }
            }
            if(uniq)
            {
                strcpy(words[index],word);
                count[index]++;
                index++;
            }
            else
            {
                count[i]++;
            }
        }
    }
   /* for (i=0;i<index;i++){
        printf("%s = %d\n",words[i],count[i]);
    }*/
    return index;
}
int levenshtein(const char *s, const char *t)
{
    if(strcmp(s,t)==0)
    {
    	return 0;
    }
    if(strlen(s)==0)
    {
    	return strlen(t);
    }
    if(strlen(t)==0)
    {
    	return strlen(s);
    }
    int len1,len2,x,y,ld,od;
    len1=strlen(s);
    len2=strlen(t);
    int column[len1+1];
    for (y=1;y<=len1;y++)
        column[y]=y;
    for (x=1;x<=len2;x++) 
    {
        column[0]=x;
        for (y=1,ld=x-1;y<=len1;y++)
        {
            od=column[y];
            column[y]=min3(column[y]+1,column[y-1]+1,ld+(s[y-1]==t[x-1]?0:1));
            ld=od;
        }
    }
    return column[len1];
}
