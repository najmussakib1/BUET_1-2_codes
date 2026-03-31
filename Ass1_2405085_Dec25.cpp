#include <iostream>
#include <string>
#include <vector>

using namespace std;
class Figure{
    int row;
    int col;
    string name;
    int **matrix;
    void initiate_matrix(int r,int c){
        row = r;
        col = c;
        matrix = new int*[row];
        for(int i=0;i<r;i++){
            matrix[i] = new int[col];
        }
    }
    void setname(){
        if(row==2){
            if(col == 2 ) name = "Straight_Line_2D";
            else if(col==3) name ="Straight_Line_3D";
            else name = "Straight_Line"+to_string(col)+"D";
        }
        else if(row==3){
            if(col == 2 ) name = "Triangle_2D";
            else if(col==3) name ="Triangle_3D";
            else name = "Triangle"+to_string(col)+"D";
        }
        else if(row==4){
            if(col == 2 ) name = "Rectangle_2D";
            else if(col==3) name ="Rectangle_3D";
            else name = "Rectangle"+to_string(col)+"D";
        }
        else {
            name = "Unknown";
        }
    }
public:
    Figure(){
        cout<<"Default constructor called"<<endl;
        row=0;
        col =0;
        name="unknown";
        matrix=nullptr;
    }
    Figure(int r,int c, int* arr){
        cout<<"Parameterized constructor called"<<endl;
        //memory allocation
        initiate_matrix(r,c);
        for(int i=0;i<r;i++){
            for(int j=0;j<c;j++){
                matrix[i][j] = arr[i*col+j];
            }
        }
        setname();
    }
    Figure(const Figure& fig){
        cout<<"Cloning constructor called"<<endl;
        row = fig.row;
        col = fig.col;
        name = fig.name;
        initiate_matrix(fig.row,fig.col);
        for(int i=0;i<fig.row;i++){
            for(int j=0;j<fig.col;j++){
                matrix[i][j] = fig.matrix[i][j];
            }
        }
    }
    ~Figure(){
        cout<<"Destructor Mode Activated"<<endl;
        row = 0;
        col = 0;
        for(int i=0;i<row;i++){
            delete[] matrix[i];
        }
        delete[] matrix;
        matrix = nullptr;
        
        cout<<name<<" has been destroyed"<<endl;
        name ="";
    }
    int getSum(){
        int sum =0;
        for(int i=0;i<row;i++){
            for(int j=0;j<col;j++){
                sum += matrix[i][j];
            }
        }
        return sum;
    }
    int getSum(int x,int y){
        if(x<=row && y<=col){
            int sum =0;
            for(int i=0;i<x;i++){
                for(int j=0;j<y;j++){
                    sum+=matrix[i][j];
                }
            }
            return sum;
        }
        else{
            cout<<"Row or column out of range"<<endl;
            return -1;
        }
    }
    string getname(){
        return name;
    }
};
int main(){
    int r,c;
    cin>>r;
    cin>>c;
    int* arr = new int[r*c];
    for(int i=0;i<r*c;i++){
        cin>>arr[i];
    }
    Figure obj1(r,c,arr);
    delete[] arr;
    cout<<obj1.getname()<<" has a sum of: "<<obj1.getSum()<<endl;
    cout<<"enter a range of row and col to find sum of 0 to (r-1) and 0 to col-1"<<endl;
    int x,y;
    cin>>x;
    cin>>y;
    cout<<obj1.getname()<<" has a sum of: "<<obj1.getSum(x,y)<<"for the value of"<<x<<","<<y<<endl;
    cout<<"Cloning obj1 named "<<obj1.getname()<<" to obj2"<<endl;
    Figure obj2(obj1);
    cout<<obj1.getname()<<" has a sum of: "<<obj1.getSum()<<endl;


    return 0;
}