package assignment07;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Scanner;

public class PathFinder 
{
	static Graph maze=null;
	static Queue<Node> correctPathSaved=new LinkedList<Node>();
	//Node Class stores and up right left and down value
	//Plus its row and column number
	//Type is if its a start finish or blank spot 0,1,2 respectively
	public static class Node
	{
		char type='p';
		int row=0;
		int column=0;
		Boolean visted=false;
		Node cameFrom=null;
		Node(int row, int column,char type)
		{
			this.row=row;
			this.column=column;
			this.type=type;
		}
		
	}
	//Graph that holds a matrix of nodes and the size of the matrix
	public static class Graph
	{
		int size=0;
		Node [] [] nodes=null;
		Graph(int x, int y)
		{
			nodes=new Node [y][x];
		}
	}
	
	
	
	
	public static void solveMaze(String inputFile, String outputFile) 
	{
		int y = 0; 
		int x=0;
		int startX=0;
		int startY=0;
		
		File mazeToBeSloved=new File(inputFile);
		
		//reading the file and making the right x and y for the matrix saved for later
		try
		{
		Scanner myReader = new Scanner(mazeToBeSloved);
			String[] dimensions = myReader.nextLine().split(" ");
//			for (int i=0;i<dimensions.length;i++)
//			{
//				System.out.println(dimensions[i]);
//			}
			
				y = Integer.parseInt(dimensions[0]);
				x = Integer.parseInt(dimensions[1]);
			//Making a graph with the x and y 
			 maze=new Graph(x,y);
			
				//reading the rest of the maze and assigning to the matrix
			 //does the counts to keep track of the row and column numbers
			 int countY=0;
			while(myReader.hasNext())
			{
				String mazeLine= myReader.nextLine();
				int countX=0;
				
				for (int i=0;i<mazeLine.length();i++)
				{
					
//					System.out.println(mazeLine.charAt(i));
					
					maze.nodes[countY] [countX]=new Node (countX,countY,mazeLine.charAt(i));
					if (mazeLine.charAt(i)=='X')
					{
						maze.nodes[countY] [countX]=null;
					}
					else if(mazeLine.charAt(i)=='S')
					{
						startX=countX;
						startY=countY;
					}
					countX++;
				
				}
				countY++;
//				System.out.println(countY+ " " + countX);
			}
			
		}catch (FileNotFoundException e)
        {
            System.out.println("An error occurred.");
            e.printStackTrace();
        }
		//Breath First Search method using a Que finds the shortest path then ends when the G is found
		//saves at the node where it came from and flags it as visted
		//will ingorn the walls since they are null
		correctPathSaved.add(maze.nodes[startY] [startX]);
		Node temp=null;
		while(!correctPathSaved.isEmpty())
		{
			temp=correctPathSaved.remove();
			temp.visted=true;
			if (temp.type=='G')
			{
				break;
			}
			//looks at up down left and right for each node
			if (maze.nodes [temp.column][temp.row-1]!=null&&maze.nodes[temp.column][temp.row-1] .visted==false)
			{
				maze.nodes [temp.column][temp.row-1].visted=true;
				maze.nodes[temp.column][temp.row-1] .cameFrom=temp;
				correctPathSaved.add(maze.nodes [temp.column][temp.row-1]);
			}
			if (maze.nodes [temp.column][temp.row+1]!=null&&maze.nodes [temp.column][temp.row+1].visted==false)
			{
				maze.nodes [temp.column][temp.row+1].visted=true;
				maze.nodes [temp.column][temp.row+1].cameFrom=temp;
				correctPathSaved.add(maze.nodes [temp.column][temp.row+1]);
			}
			if (maze.nodes[temp.column+1][temp.row] !=null&&maze.nodes[temp.column+1][temp.row] .visted==false)
			{
				maze.nodes[temp.column+1][temp.row] .visted=true;
				maze.nodes[temp.column+1][temp.row] .cameFrom=temp;
				correctPathSaved.add(maze.nodes[temp.column+1][temp.row] );
			}
			if (maze.nodes[temp.column-1][temp.row]  !=null&&maze.nodes[temp.column-1][temp.row] .visted==false)
			{
				maze.nodes[temp.column-1][temp.row] .visted=true;
				maze.nodes[temp.column-1][temp.row] .cameFrom=temp;
				correctPathSaved.add(maze.nodes[temp.column-1][temp.row] );
			}
		}
		
		//traces back the path from G adding .
		if (temp.type=='G')
		{
		while (!(temp.cameFrom.type=='S'))
		{
			temp=temp.cameFrom;
			temp.type='.';
		}
		}
		else
		{
			System.out.println("THAT WAS IMPOSSABLE");
		}	
		//just prints out the array to a file with the sizes at the top
		try 
		{
			PrintWriter output = new PrintWriter
			(new FileWriter(outputFile));
			output.print(y+" "+x+"\n");
			for (int i=0;i<y;i++)
			{
				for (int j=0;j<x;j++)
				{
					if (maze.nodes[i][j]!=null)
					{
					output.print(maze.nodes[i][j].type);
					}else
					{
						output.print('X');
					}
				}
				output.print("\n");
			}
			output.flush();
			output.close();
		} catch (IOException e) 
		{
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		System.out.println("Maze is Done");
		
		
		
		
		
		
		
		
		
		
		
		
		
//		for (int i=0;i<9;i++)
//		{
//			
//				System.out.println(maze.nodes[0] [i].type+ ' '+maze.nodes[1] [i].type+ ' '+maze.nodes[2] [i].type+ ' '+maze.nodes[3] [i].type+ ' '+maze.nodes[4] [i].type+ ' '+maze.nodes[5] [i].type+ ' '+maze.nodes[6] [i].type);
//			
//		}
		
		
		
		
		
		
	}
}
;