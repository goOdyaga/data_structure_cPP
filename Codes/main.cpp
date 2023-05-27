#include <iostream>
#include "StackH.h"
// #include<stack>
#include <vector>
#include <cstdlib>
#include <ctime>
#include<fstream>
#include<string>
using namespace std;



// Define a class for a cell in the maze
class Cell {
    public:

    int row, col;
    bool visited;
    bool top_wall, right_wall, bottom_wall, left_wall;
    Cell()
    {

    }

    Cell(int r, int c) {
        row = r;
        col = c;
        visited = false;
        top_wall = true;
        right_wall = true;
        bottom_wall = true;
        left_wall = true;
    }
};


// Function to create the maze
vector<vector<Cell>> createMaze(int rows, int cols,string filename ) 
{
    std::ofstream output_file(filename);
    // Create the grid of cells
    vector<vector<Cell>> grid(rows, vector<Cell>(cols, Cell(0, 0)));
    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<cols;j++)
        {
            grid[i][j].row=i;
            grid[i][j].col=j;
        }
    }
    // Choose a random starting cell and mark it as visited
    srand(time(NULL));
    int start_row = rand()%rows;
    int start_col = rand()%cols;
    grid[start_row][start_col].visited = true;

    // Create a stack for backtracking
    StackH<Cell> back_stack;

    // Add the starting cell to the stack
    back_stack.push(grid[start_row][start_col]);

    // Loop until the stack is isEmpty
    while (!back_stack.empty()) 
    {

        // Pop the top cell from the stack
        Cell current = back_stack.top();
        back_stack.pop();

        // Get the neighbors of the current cell
        vector<Cell> neighbors;

        // Check the cell above the current cell
        if (current.row > 0 && !grid[current.row-1][current.col].visited) {
            neighbors.push_back(grid[current.row-1][current.col]);
        }

        // Check the cell to the right of the current cell
        if (current.col < cols-1 && !grid[current.row][current.col+1].visited) {
            neighbors.push_back(grid[current.row][current.col+1]);
        }

        // Check the cell below the current cell
        if (current.row < rows-1 && !grid[current.row+1][current.col].visited) {
            neighbors.push_back(grid[current.row+1][current.col]);
        }

        // Check the cell to the left of the current cell
        if (current.col > 0 && !grid[current.row][current.col-1].visited) {
            neighbors.push_back(grid[current.row][current.col-1]);
        }

        // If there are unvisited neighbors, choose one at random and remove the wall between it and the current cell
        if (!neighbors.empty()) 
        {
            // Choose a random neighbor
            int index = rand() % neighbors.size();

            Cell next = neighbors[index];

            // Remove the wall between the current cell and the chosen neighbor
            if (next.row == current.row - 1) 
            {
                current.top_wall = false;
                next.bottom_wall = false;
            }
            else if (next.col == current.col + 1) 
            {
                current.right_wall = false;
                next.left_wall = false;
            }
            else if (next.row == current.row + 1) 
            {
                current.bottom_wall =false;
                next.top_wall = false;
            }
            else if (next.col == current.col - 1) 
            {
                current.left_wall = false;
                next.right_wall = false;
            }
        // Mark the chosen neighbor as visited and push it onto the stack
            grid[current.row][current.col]= current;
            grid[current.row][current.col].visited = true;
            grid[next.row][next.col]= next;
            grid[next.row][next.col].visited = true;
            back_stack.push(current);
            back_stack.push(next);
        }
    }

    output_file<<grid.size()<<" "<<grid[0].size()<<endl;
    for(int i=0;i<grid.size();i++)
    {
        for(int j=0;j<grid[0].size();j++)
        {
            output_file<<"x="<<j<<" y="<<i<<" l="<<grid[grid.size()-i-1][j].left_wall<<" r="<<grid[grid.size()-i-1][j].right_wall<<" u="<<grid[grid.size()-i-1][j].top_wall<<" d="<<grid[grid.size()-i-1][j].bottom_wall<<endl;
        }
    }
    return grid;
}

//Function for solve the maze
void solve_maze(vector<vector<Cell>> grid,int start_x,int start_y,int finish_x,int finish_y,string filename)
{
    int rows=grid.size();
    int cols=grid[0].size();
    //decleare a vector that  contain every cell by a visiting position
    vector<vector<bool>> control_visit(grid.size(),vector<bool>(grid[0].size(),false));
    
    StackH<Cell> backgrand;
    int lasty=start_x;
    int lastx=grid.size()-1-start_y;
    start_x=lastx;
    start_y=lasty;

    //initial starting locaiton to visited
    control_visit[start_x][start_y]=true;

    //push starting location to stack
    backgrand.push(grid[start_x][start_y]);

    while(!backgrand.empty())
    {
        // cout<<"**"<<endl;
        Cell current=backgrand.top();
        // cout<<current.row<<"  "<<current.col<<endl;
        backgrand.pop();
        vector<Cell> neighbors;

        if (current.row > 0 && !control_visit[current.row-1][current.col]) {
            if(!current.top_wall&&!grid[current.row-1][current.col].bottom_wall)
                neighbors.push_back(grid[current.row-1][current.col]);
        }

        // Check the cell to the right of the current cell
        if (current.col < cols-1 && !control_visit[current.row][current.col+1]) {
            if(!current.right_wall&&!grid[current.row][current.col+1].left_wall)
            {
            // cout<<"2";

                neighbors.push_back(grid[current.row][current.col+1]);
            }
        }

        // Check the cell below the current cell
        if (current.row < rows-1 && !control_visit[current.row+1][current.col]) {
            if(!current.bottom_wall&&!grid[current.row+1][current.col].top_wall)
            {
            // cout<<"3";

                neighbors.push_back(grid[current.row+1][current.col]);
            }
        }

        // Check the cell to the left of the current cell
        if (current.col > 0 && !control_visit[current.row][current.col-1]) {
            if(!current.left_wall&&!grid[current.row][current.col-1].right_wall)
            {
            // cout<<"4";

                neighbors.push_back(grid[current.row][current.col-1]);
            }
        }

        if(!neighbors.empty())
        {
            // cout<<"000"<<endl;
            //select random cell from valid neighbours
            int index = rand() % neighbors.size();
            
            //initialzie next cell
            Cell next = neighbors[index];

            //visited situation of the cell initialized to tru
            control_visit[next.row][next.col]=true;
            
            //new cells stacked
            backgrand.push(current);
            backgrand.push(next);

            //if lst cell's location same as target location , whilem loop will ended
            if(next.col==finish_x&&next.row==(grid.size()-finish_y-1))
            {
                // cout<<"-----"<<endl;
                break;
            }
        }
    }

    StackH<Cell> result;
    //beacuse of locations are stacked , order off Cell's are will be reverse
    //use new stack solve this problem
    while (!backgrand.empty())
    {
        result.push(backgrand.top());
        backgrand.pop();
        /* code */
    }
    std::ofstream output_file(filename);
    while (!result.empty())
    {
        output_file<<grid.size()-1- result.top().row<<"  "<<result.top().col<<endl;
        result.pop();
    }
    
}

int main() {
    int K,M,N;

    cout<<"Enter the number of the mazes: ";
    cin>>K;
    cout<<"Enter the number of rows and columns: ";
    cin>>M>>N;
    vector<vector<vector<Cell>>> All_gridS;
    for (int i = 0; i < K; i++)
    {
        All_gridS.push_back(createMaze(M,N,"maze_"+to_string(i+1)+".txt"));

        /* code */
    }
    
    cout<<"Enter a maze ID between 1 to "+to_string(K)+" inclusive to find path: ";
    int input;
    cin>>input;
    int start_x,start_y,finish_x,finish_y;
    cout<<"Enter x and y coordinates of the entry points (x,y) or (column,row): ";
    cin>>start_y>>start_x;
    cout<<"Enter x and y coordinates of the exit points (x,y) or (column,row): ";
    cin>>finish_y>>finish_x;
    solve_maze(All_gridS[input-1],start_x,start_y,finish_x,finish_y,"maze_"+to_string(input)+"_path_"+to_string(start_y)+"_"+to_string(start_x)+"_"+to_string(finish_y)+"_"+to_string(finish_x)+".txt");
return 0;
}