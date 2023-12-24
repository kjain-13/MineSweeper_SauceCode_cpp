#include<iostream>
#include<vector>
#define N 10
#define bomb 10
#define space '_'
#define space_view '*'
#define bmb_sym '^'
#define diff_sym '#'
using namespace std;

vector<vector<char>> create(vector<vector<char>> p){
    for(int i=0;i<N;i++){
        vector<char> q;
        for(int j=0;j<N;j++){
            q.push_back(space);
        }
        p.push_back(q);
    }
    return p;
}

void print(vector<vector <char>> matrix ){
    cout << endl;
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            cout << matrix[i][j] << " ";       
        }
        cout << endl;
    }
    cout << endl;
}

bool isValidMove(int x, int y) {
    return (x >= 0 && x < N && y >= 0 && y < N);
}

vector<vector<char>> recu_prog(vector<vector<char>> p, vector<vector<char>> q , int x , int y){
    int i = -1 , j = -1;
    while(i < 2){
        j = -1;
        while(j < 2){
            if(x+i < N && y+j < N && x+i >= 0 && y+j >= 0 && q[x+i][y+j]  == space){
                if(p[x+i][y+j] == space){
                    q[x+i][y+j] = space_view;
                    q = recu_prog(p,q,x+i,y+j);
                }
                else{
                    q[x+i][y+j] = p[x+i][y+j];
                }
            }
            j++;
        }
        i++;
    }
    return q;
}

vector<vector<char>> hints(vector<vector<char>> p ,int x ,int y){
    int i = -1,j = -1;
    while(i < 2){
        j = -1;
        while(j < 2){
            if(isValidMove(x+i,y+j)){
                if(p[x+i][y+j] != bmb_sym){
                    switch(p[x+i][y+j]){
                        case space :
                            p[x+i][y+j] = '1';
                            break;
                        case '1':
                            p[x+i][y+j] = '2';
                            break;
                        case '2':
                            p[x+i][y+j] = '3';
                            break;
                        case '3':
                            p[x+i][y+j] = '4';
                            break;
                        case '4':
                            p[x+i][y+j] = '5';
                            break;
                        case '5':
                            p[x+i][y+j] = '6';
                            break;
                        case '6':
                            p[x+i][y+j] = '7';
                            break;
                        case '7':
                            p[x+i][y+j] = '8';
                            break;
                        default:
                            break;
                    }
                }
            }
            j++;
        }
        i++;
    }
    return p;
}

vector<vector<char>> plant_bomb(vector<vector<char>> p){
    int plant = bomb;
    while(plant > 0){
        
        int x = rand()%N ,y = rand()%N ;
        if( p[x][y] == bmb_sym){
            plant++;
        }
        else{
            p[x][y] = bmb_sym;
            p = hints(p,x,y);
        }
        plant--;
    }
    return p;
}

bool chk_win(vector<vector<char>> p , vector<vector<char>> q){
    int count = 0;
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            if(p[i][j] == bmb_sym && q[i][j] == diff_sym){
                count++;
            }
        }
    }
    if(count == bomb){
        return true;
    }
    else{
        return false;
    }
}

int main(){
    vector<vector<char>> solution_matrix,view_grid ;
    int x,y,flag = 1,counter = 0;
    char choice;
    solution_matrix = create(solution_matrix);
    view_grid = create(view_grid);
    print(view_grid);
    solution_matrix = plant_bomb(solution_matrix);
    print(solution_matrix); //the solution matrix;
    while(flag == 1){
    cout << "Enter Your Choice: \n p for play \n d for diffuse \n u for undiffuse \n q for quit \n " ;
    cin >> choice;
    if(choice == 'p'){
        cout << "Enter the coordinates to be checked : " ;
        cin >> x >> y;
        if(isValidMove(x,y)){
            if(solution_matrix[x][y] != bmb_sym){
                if(solution_matrix[x][y] == space){
                    // reccursive program for blank spaces 
                    view_grid[x][y] = space_view;
                    view_grid = recu_prog(solution_matrix,view_grid,x,y);
                }
                else{
                    view_grid[x][y] = solution_matrix[x][y];
                }
                print(view_grid);
            }
            else{
                flag = 0;
            }
        }
        else{
            cout << "Invalid Coordinates " << endl;
        }
    }
    else if ( choice == 'd'){
        if(counter != bomb){
            cout << "Enter the coordinates to be diffused : " << endl;
            cin >> x >> y;
            if(view_grid[x][y] == space){
                view_grid[x][y] = diff_sym;
                counter++;
            }
            else{
                cout << "Already Diffuse You Blind Man:" << endl;
            }
        }
        else{
            cout << "You do Not have Enough Red Flags : " << endl;
        }
        // diffuse code 
    }
    else if (choice == 'q'){
        flag = 0;
    }
    else if( choice == 'u'){
        if(counter != 0){
            cout << "Enter the coordinates to be undiffused : " << endl;
            cin >> x >> y;
            if(view_grid[x][y] = diff_sym){ 
                counter--;
            }
            else{
                cout << "No Red Flags Here "<< endl;
            }
        }
        else{
            cout << "You Smart Boi Place Some Red Flags First " << endl;
        }
    }
    else{
        cout << "Invalid input " << endl;
    }
    }
    if(chk_win(solution_matrix,view_grid)){
        cout << "You Win :) " << endl;
    }
    else{
        cout << "You Lose :( " << endl;
        print(solution_matrix);
    }
    return 0;
}
