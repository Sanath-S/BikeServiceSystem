//final
#include<fstream>
#include<string>
#include<iostream>
#include<sstream>
#include<stdio.h>

using namespace std;

class Bike
 {
  public:
  	string uname;
	string paswd;
	string brand;
  	string buffer,bufferi;
	string cost;
	string serialNo;
	int count;
	int adrs_list[100];
	string serial_list[100];
	void alogin(string admin,string pass);
	void bikeAdd();
	void bikePack();
	void write();
	string extract_sno();
	int remove(string);
	void unpack();
	int bikeSearch(string key);
	int bikeDel(string);
	void bikeMod(string);
        void create_index();
        void sort_index();
        int search_index(string);
        int brandSearch(string);
	
 };
 
 void Bike::alogin(string admin,string pass)
 {
  uname=admin;
  paswd=pass;
  ifstream out;
	out.open("Bikes.txt", ios::in | ios::app);
	out.close();
 }

 void Bike::bikeAdd()
 {
	cout <<"Enter the details \n";
	cout<<" Serial No: ";
    	cin>>serialNo;
    	cout<<" Brandname: ";
    	cin>>brand;
    	cout<<" Cost: ";
    	cin>>cost;
 }

 void Bike::bikePack()
 {
	buffer.erase();
   	buffer+=serialNo+"|"+brand+"|"+cost+"$"+"\n";
     
 }
 void Bike::write()
 {
 	int pos;
 	fstream file,file1;
 	file.open("Bikes.txt",ios::out | ios::app);
	pos=file.tellp();
 	file<<buffer;
    	file.close();
    	serial_list[++count]= serialNo;
  	adrs_list[count]=pos;
  	
  	 file1.open("Index.txt",ios::out|ios::app);
        bufferi.erase();
        string st;
        ostringstream convert;
        convert<<pos;
        st=convert.str();
        bufferi+=st+"  "+serialNo+""+"\n";
        file1<<bufferi;
        file1.close();
        sort_index();
  	  	 	
  }
  
   
  string Bike::extract_sno()
  {
  	string serialNo;
  	int i=0;
  	serialNo.erase();
  	while(buffer[i]!='|')
  	serialNo+=buffer[i++];
  	return serialNo;
  }
  void Bike::create_index()
  {
  	fstream file;
  	int pos;
  	count=-1;
  	string serialNo;
	file.open("Bikes.txt",ios::in);
	while(!file.eof())
	{
		pos=file.tellg();
		buffer.erase();
		getline(file,buffer);
		if(buffer[0]!='*')
                {
                	if(buffer.empty())
                	break;
                	  serialNo=extract_sno();
                	  serial_list[++count]= serialNo;
  			  adrs_list[count]=pos;
  		}
  	}
  	file.close();
  	sort_index();
     	buffer.erase();
     	
  }
  
 void Bike::sort_index()
 {
 	string temp_sno;
 	int temp_add,i,j;
 	fstream file;
 	file.open("Index.txt",ios::out);
 	for(i=0;i<=count;i++)
 	{
 		for(j=i+1;j<=count;j++)
 		{
 			if(serial_list[i]>serial_list[j])
 			{
 				temp_sno=serial_list[i];
 				serial_list[i]=serial_list[j];
 				serial_list[j]=temp_sno;
 				temp_add=adrs_list[i];
 				adrs_list[i]=adrs_list[j];
 				adrs_list[j]=temp_add;
 			}
 		}
 	}
 	 	for(i=0;i<=count;i++)
 	 	{
 	 	 file<<serial_list[i]<<"\t"<<adrs_list[i]<<"\n";
 		}
 		file.close();		
 }
 	
 int Bike::search_index(string key)
{
	int low=0,high=count,mid=0,flag=0,pos;
        while(low<=high)
        {
        	mid=(low+high)/2;
                if(serial_list[mid]==key){flag=1;break;}
                if(serial_list[mid]>key)high=mid-1;
                if(serial_list[mid]<key)low=mid+1;
        }
        if(flag)
        return mid;
        else
        return -1 ;
}

int Bike::remove(string key)
{
	int pos=0,i,address,flag;
	fstream file;
	pos=search_index(key);
	if(pos>=0)
	{
		file.open("Bikes.txt",ios::out | ios::in);
		address=adrs_list[pos];
		file.seekp(address,ios::beg);
		file.put('*');
		file.close();
		flag=1;
		cout<<"\nBike deleted\n";
		for(i=pos;i<count;i++)
		{
			serial_list[i]=serial_list[i+1];
			adrs_list[i]=adrs_list[i+1];
		}
		count--;
	}
	else
	{
        	flag=0;
   	}
    	if(flag==1) return 1;
    	else
        return 0;
}
	

 void Bike::unpack()
{
        int i=0;
        serialNo.erase();
        while(buffer[i]!='|')
                 serialNo+=buffer[i++];
        brand.erase();
        i++;
        while(buffer[i]!='|')
                 brand+=buffer[i++];
        cost.erase();
        i++;
        while(buffer[i]!='$')
                 cost+=buffer[i++];
}


 int Bike::bikeSearch(string key)
 {
	 ifstream file;
        int flag=0,pos=0;
        file.open("Bikes.txt",ios::in);
        while(!file.eof())
        {
                buffer.erase();
                pos=file.tellg();
                getline(file,buffer);
                 unpack();
                if(key==serialNo)
                {
                       cout<<"\nfound the key,the record is...\n"<<buffer;
                       return pos;
                }
        }
        file.close();
        if(flag==0)
        {
                cout<<"\n Not found \n";
                return -1;
	 }
 }
 
 int Bike::brandSearch(string key)
 {
	 ifstream file;
	 
        int flag=0,pos=0;
        
        file.open("Bikes.txt",ios::in);
        while(!file.eof())
        {
                buffer.erase();
                pos=file.tellg();
                getline(file,buffer);
                 unpack();
                if(key==brand)
                {
                	
                        int n;
			istringstream is(cost);
			is>>n;
			int n1=(0.16*n)+n; 	//transaction
			
			return n1;

                       flag=1;                     
                }
        }
        file.close();
        if(flag==0)
        {
                cout<<"\n Not found \n";
                
	 }
	                               
 }

  int Bike::bikeDel(string key)
 {
	    fstream file;
        int pos, flag=0;
        pos=bikeSearch(key);
        if(pos>=0)
        {
                file.open("Bikes.txt");
                file.seekp(pos,ios::beg);
                file.put('*');
                flag=1;
                file.close();
        }
        if(flag==1) 
          return 1;
        else
          return 0;

 }

  void Bike::bikeMod(string key)
 {
	    int c;
        if(bikeDel(key))
        {
                cout<<"\nSelect to modify:\n1:Serial No\n2:Brand Name \n3:Cost \n";
                cin>>c;
                switch(c)
                {
                        case 1:cout<<"Serial No: \n";
                               cin>>serialNo;
                               break;
                        case 2:cout<<"Brand Name:\n";
                               cin>>brand;
                               break;
                        case 3:cout<<"Cost: \n";
                               cin>>cost;
                               break;
                        default:cout<<"wrong choice\n";
                }
                buffer.erase();
                bikePack();
	        write();
		}
 }
 

 class Users 
 {
  public:
  	string name;
  	string id;
  	string buffer;
  	string pno;
  	string city,city1;
  	string add;
  	string date;
  	void newuser();
    	int ulogin();
    	void uReg();
    	void write();
	void unpack();
    	string compr(string);
        string dcompr(string);
  	
  };
  
  
  int Users::ulogin()
  {
   string id1;
   fstream file;
    int flag=0,pos=0;
   cout<<"Enter ID number\n";
	cin>>id1;
   file.open("usr.txt",ios::in);
    while(!file.eof())
        {
                buffer.erase();
                pos=file.tellg();
                getline(file,buffer);
                 unpack();
                if(id1==id)
                {
                       
                       return 1;
                }
        }
    file.close();
     write();
  }

  void Users::unpack()
{
        int i=0;
        id.erase();
        while(buffer[i]!='|')
                 id+=buffer[i++];
        name.erase();
        i++;
        while(buffer[i]!='|')
                 name+=buffer[i++];
        pno.erase();
        i++;
        while(buffer[i]!='|')
                 pno+=buffer[i++];
		city.erase();
		i++;
        while(buffer[i]!='|')
                 city+=buffer[i++];
		add.erase();
		i++;
        while(buffer[i]!='|')
                 add+=buffer[i++];
                 date.erase();
                 i++;
         while(buffer[i]!='$')
         	 date+=buffer[i++];
}
 
  void Users::uReg()
  {
   cout<<"\nEnter ID number : ";
   cin>>id;
   cout<<"\nEnter Username : ";
   cin>>name;
   cout<<"\nEnter phone no. : ";
   cin>>pno;
   cout<<"\nEnter City : ";
   cin>>city;
   city1=compr(city);
   cout<<"\nEnter Address : ";
   cin>>add;
   cout<<"\nEnter Date of Sevice [dd/mm/yyyy]: ";
   cin>>date;
  }
  
  void Users:: write()
  {
   buffer.erase();
   buffer+=id+"|"+name+"|"+pno+"|"+city1+"|"+add+"|"+date+"$"+"\n";
   fstream file;
   file.open("usr.txt",ios::out | ios::app);
   file<<buffer;
   file.close();
  }
  
  string Users::compr(string city)
  {
  	if(city=="bengaluru" || city=="BENGALURU" || city=="bangalore" || city=="Bangalore")
	return "BLR";
	else if(city=="CHENNAI" || city=="chennai")
	return "CHN";
	else if(city=="VISHAKPATNAM" || city=="vishakpatnam")
	return "VP";
	else 
	return "INVALID CITY";
  }
   string Users::dcompr(string city1)  
   {
   	if(city1=="BLR")
   	return "BENGALURU";
   	else if(city1=="CHN")
   	return "CHENNAI";
   	else if(city1=="VP")
   	return "VISHAKPATNAM";
   	else 
   	return "INVALID CITY";
   }
   
   	
 int main()
 {
	int ch,ch1,ch2,i,t1;
	string ch3;
	string uname,str;
	string paswd;
	string key;
	Bike b;
	Users u;
	system("clear");
 	cout<<"\t\t BIKE SERVICES \n";
	
	 start: cout<<"  -----MENU-----\n";
	 cout<<" 1--> ADMIN\n 2--> USER\n 3--> Exit\n";
	 cout<<" WHO R U.. ?\n";
	 cin>>ch;
	 switch(ch)
	 {
 	  case 1: cout<<"Enter username\n";
 	  	  cin>>uname;
 	  	  cout<<"Enter Password\n";
 	  	  cin>>paswd;
 	  	  if (uname == "root" && paswd == "toor")
			{
			b.alogin(uname,paswd);
			cout<<"\nAuthentication Success..\n";
			
			}
			else
			{
			 cout<<"Fail\n";
			 goto start;
			 }
		    label1:cout<<" \nInput Your Choice\n 1--Add\n 2--Delete\n 3--Modify\n 4--Search\n 5--Logout\n";
		    cin>>ch2;
		    switch(ch2)
		    {
		       case 1: {
		       		 b.bikeAdd();
			   		b.bikePack();
				  	 b.write();
				  	 goto label1;
			       }
		       		break;

		       case 2: {
		       		cout<<"\n Enter the serial number:\n";
                    		cin>>key;
                      	   	i=b.remove(key);
               			if(i==1)
                     		cout<<"Click Add to include more services\n";
              			 else
                     		cout<<"\nBike not deleted \n";
                     		goto label1;
                     		}
		       		break;

		       case 3:{
		       		 cout<<"\nEnter the serial number:\n";
                       		 cin>>key;
                       		 b.bikeMod(key);
                        	 //b.remove(key);
                        	 goto label1;
                              }
		       		break;

		       case 4:{
		       		 cout<<"\nEnter the key:\n";
                   		     cin>>key;
                      		  b.bikeSearch(key);
                      		  goto label1;
                      		}
		       		break;

		       case 5: goto start;
		       		break;
		    }
		    
			break;
		
	  case 2:{
	  	 Users u;
	  	  cout<<"\n WELCOME CUSTOMER\n";
	  	 label2:cout<<" 1-->SignIn\n 2-->SignUp\n 3-->Exit\n";
	  	 cout<<" Enter your choice\n";
	  	 cin>>ch1;
	  	 switch(ch1)
	  	 {
	  	  case 1:{
	  	  	  int i=u.ulogin();
	  	  	  if(i==1)
	  	  	  {
	  	  	    cout<<"\nAuthentication Successful!!!\n";
	  	  	    cout<<"\nChoose Your Bike:\n\n*BENELLI\n*KTM\n*HONDA\n*YAMAHA\n\n";
	  	   		cin>>ch3;
	  	   		t1=b.brandSearch(ch3);
	  	   		
	  	       cout<<"----------------------------------------------------\n";
                       cout<<"        		 SUMMARY 		          \n";
                       cout<<"----------------------------------------------------\n";
                       cout<<"\n";
                       cout<<"  UserID: "<<u.id<<endl;
                       cout<<"  Serial no.: "<<b.serialNo<<endl;
                       cout<<"  Brand: "<<b.brand<<endl;
                       str=u.dcompr(u.city1);
                       cout<<"  City: "<<str<<endl;
                       cout<<"  Service Date: "<<u.date<<endl; 
                       cout<<"\n";
                       cout<<"  Total Cost: Rs "<<t1<<"/-"<<endl;
                       cout<<"\n\n Total Cost is inclusive of 16 percentage of tax.\n";
                       cout<<"\n Our service team will visit you at your covinience.\n";
                       cout<<"----------------------------------------------------\n";
                       cout<<"____________________________________________________\n";
	  	  	   }
	  	  	    else{
	  	  	     cout<<"Didnt work..Try Again..!!..\n";
	  	  	     goto label2;
	  	  	  }
	  	  	  }
	  	 		 break;
	  	  case 2: {
	  	  	   u.uReg();
			   u.write();
	  	  	   cout<<"\nRegistered Successfully... \n\n Please SignIn\n";
	  	  	   goto label2;
	  	           }
	  	          break;
	  	          
	  	   
	  	  case 3:
	  	  	 goto start ;
	  	  	 
	  	  	break;
	  	  }
	  	 break;
	  	 }
	  case 3: {return 0;}
		break;
	  
	 }
	
		
  }
