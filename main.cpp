#include <iostream>
#include<fstream>
#include <sstream>
using namespace std;
float input_data_array[10000];
int input_data_quantity=0;
const int kMeanQuantity=2;
const int kGroupQuantity=4;
#define FILENAME ".\\data\\real_7752.txt"
float mean_array[10000];
int mean_counter=0;

string SAX_array[10000];
int SAX_counter=0;
const double kSAXRange=0.5;

int SAXtoChar(float difference,float rawData);
void Mean();
void Sax(int standard,int counter,float *tempArray);
void Group();
void InputData();

int main()
{
    InputData();
    Mean();
    Group();

    for(int i=0;i<=SAX_counter;i++){
       cout<<SAX_array[i]<<endl;
    }

    return 0;
}

void InputData(){
    ifstream f;
    f.open(FILENAME);
    while (!f.eof()){
        f >> input_data_array[input_data_quantity];
        input_data_quantity++;
    }
    f.close();

}


void Mean(){


  mean_counter=0;
  float mean=0;

  for(int i=0;i<input_data_quantity;i++){
    if((i%kMeanQuantity)==0&&i!=0){
      mean=mean/kMeanQuantity;
      mean_array[mean_counter]=mean;
      mean_counter++;
      mean=0;

    }
     mean=mean+input_data_array[i];
  }
}

void Group(){
    int standard=0;
    float tempArray[mean_counter];
    for(int i=0;i<=mean_counter;i++){
         if((i%kGroupQuantity)==0&&i!=0){
            Sax(standard,i,tempArray);
            standard=i;
        }
        tempArray[i]=mean_array[i];
    }

}

void Sax(int standard,int counter,float *tempArray){

   float groupStandard=tempArray[standard];

   int firstStandard=tempArray[standard];
   stringstream ss;
   ss << firstStandard;
   SAX_array[SAX_counter]=ss.str();
   SAX_counter++;


   for(int i=standard+1;i<counter;i++){
        float difference=tempArray[i]-groupStandard;
        if(SAXtoChar(difference,tempArray[i])==1){
            groupStandard=tempArray[i];
            cout<<"azusa"<<endl;
        }

   }

}

int SAXtoChar(float difference,float rawData){
  int symbolNumber;
  float minRange=(kSAXRange*-1)*27;
  float maxRange=kSAXRange*27;
  float interval=0;
  if(difference<minRange){
    stringstream ss;
    ss << rawData;
    SAX_array[SAX_counter]=ss.str();
    SAX_counter++;
    return 1;
  }
  else if(difference>maxRange){
    stringstream ss;
    ss << rawData;
    SAX_array[SAX_counter]=ss.str();
    SAX_counter++;
    return 1;
  }

  if(difference>0){
    for(symbolNumber=1;symbolNumber<=26;symbolNumber++){
        interval=interval+kSAXRange;
        if(difference<interval){
            SAX_array[SAX_counter]=char(96+symbolNumber);
            SAX_counter++;
            return 0;
        }
    }
  }
  else{
    for(symbolNumber=1;symbolNumber<=26;symbolNumber++){
        interval=interval-kSAXRange;
        if(difference>interval){
            SAX_array[SAX_counter]=char(64+symbolNumber);
            SAX_counter++;
            return 0;
        }
    }
  }
}
