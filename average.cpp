#include <iostream>

using namespace std;

int main(int argc, char* argv[]){
    double sum = 0;
    double result;
    if(argc == 1){
        cout << "Please input numbers to find average.";
    }else{
        for(int i = 1; i < argc; i++){
            sum += atof(argv[i]);
        }
        result = sum / (argc-1) ;
        cout << "---------------------------------" << endl;
        cout << "Average of " << argc-1 << " numbers = " << result << endl;
        cout << "---------------------------------";
    }
}
