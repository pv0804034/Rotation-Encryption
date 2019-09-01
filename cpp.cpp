#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
using namespace std;

string encrypt(vector<vector<char> > matrix,int key){
    int M = matrix.size();
    int N = matrix[0].size();
    int numRings = min(M,N)/2;
    for(int i = 0; i < numRings; i++) {
        // Subtract the number of 360 degree rotations from R
        // A 360 degree rotation = rotating the same number of times as the perimeter of the current ring
        int numRotations = key%(2*(M + N - 4*i) - 4);
        for(int rotation = 0; rotation < numRotations; rotation++) {
            // Rotate the ring (see the clockwise algorithm for an in-depth example of how this is done)
            // Rotate top row
            for(int j = i; j < N-i-1; j++) {
                int tmp = matrix[i][j];
                matrix[i][j] = matrix[i][j+1];
                matrix[i][j+1] = tmp;
            }
            // Rotate right column
            for(int j = i; j < M-i-1; j++) {
                int tmp = matrix[j][N-i-1];
                matrix[j][N-i-1] = matrix[j+1][N-i-1];
                matrix[j+1][N-i-1] = tmp;
            }
            // Rotate bottom row
            for(int j = N-i-1; j > i; j--) {
                int tmp = matrix[M-i-1][j];
                matrix[M-i-1][j] = matrix[M-i-1][j-1];
                matrix[M-i-1][j-1] = tmp;
            }
            // Rotate left column
            for(int j = M-i-1; j > i+1; j--) {
                int tmp = matrix[j][i];
                matrix[j][i] = matrix[j-1][i];
                matrix[j-1][i] = tmp;
            }
        }
    }
    string s = "";
    for(int i = 0;i<M;i++){
        for(int j = 0;j<N;j++){
            s += matrix[i][j];
        }
    }
    return s;
}

vector<vector<char> > makeVector(string s){
    int n = sqrt(s.size());
    int m = n;
    if(n*m < s.size())m++;
    vector<vector<char> >vec(n,vector<char>(m,32));
    int x = 0;
    for(int i = 0;i<n;i++){
        for(int j = 0;j<m;j++){
            if(x < s.size()){
                vec[i][j] = s[x];
            }
            x++;
        }
    }
    return vec;
}

string decrypt(string s, int key){
    vector<vector<char> > matrix = makeVector(s);
    int M = matrix.size(),N = matrix[0].size();
    int numRings = min(M,N)/2;
    for(int i = 0; i < numRings; i++) {
        // Subtract the number of 360 degree rotations from R
        // A 360 degree rotation = rotating the same number of times as the perimeter of the current ring
        int numRotations = key%(2*(M + N - 4*i) - 4);
        for(int rotation = 0; rotation < numRotations; rotation++) {

            // Rotate top row
            for(int j = N-i-1; j > i; j--) {
                int tmp = matrix[i][j];
                matrix[i][j] = matrix[i][j-1];
                matrix[i][j-1] = tmp;
            }
            // Rotate left column
            for(int j = i; j < M-i-1; j++) {
                int tmp = matrix[j][i];
                matrix[j][i] = matrix[j+1][i];
                matrix[j+1][i] = tmp;
            }
            // Rotate bottom row
            for(int j = i; j < N-i-1; j++) {
                int tmp = matrix[M-i-1][j];
                matrix[M-i-1][j] = matrix[M-i-1][j+1];
                matrix[M-i-1][j+1] = tmp;
            }
            // Rotate right column
            for(int j = M-i-1; j > i+1; j--) {
                int tmp = matrix[j][N-i-1];
                matrix[j][N-i-1] = matrix[j-1][N-i-1];
                matrix[j-1][N-i-1] = tmp;
            }
        }
    }
    string message = "";

    for(int i = 0;i<M;i++){
        for(int j = 0;j<N;j++){
            message += matrix[i][j];
        }
    }
    return message;
}

int main(){
    ifstream cin;
    cin.open("input.txt");
    ofstream cout;
    cout.open("output.txt", ios::out | ios::trunc);
    string message;
    getline(cin,message);
    int key;
    cin>>key;
    cout<<message.size()<<endl;
    vector<vector<char> >vec = makeVector(message);
    string chiperText = encrypt(vec,key);
    string planeText = decrypt(chiperText,key);

    cout<<chiperText<<endl;
    cout<<planeText<<endl;
    return 0;
}
