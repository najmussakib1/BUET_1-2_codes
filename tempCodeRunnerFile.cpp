int main(){
    int r,c;
    cin>>r>>c;
    int arr[r*c];
    for(int i=0;i<r*c;i++){
        cin>>arr[i];
    }
    
    Figure Triangle2D(r,c,arr);
    cout<<Triangle2D.getname()<<" has a sum of: "<<Triangle2D.getSum()<<endl;


    return 0;
}