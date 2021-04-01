/*
  Author: Michael Hon
  Email: mhon2014@my.fit.edu
  Course: CSE2010
  Section: E4
  Description: HW6 Java Graph implementation.

 */


import java.util.HashMap;
import java.util.LinkedList;
import java.util.Scanner;
import java.io.*;


//Ryan said "Hello Thotmas Haskellbasket"
//please don't roast my code.
class node{
    public String name; //name of the vertex
    public LinkedList<node> neighbors; //list of neighbors
    
    //constructor
    public node(){
        this.name = null;
        this.neighbors = new LinkedList<node>();
    }

    //function to just set the name of the node.
    public void setName(String arg_name){
        this.name = arg_name;
    }

    //return the list of neighbors of the current node
    public LinkedList<node> getNeighbors(){
        return this.neighbors;
    }

    //function to check if vertex contains a neighbor
    public boolean containsNeighbor(String arg_name){
        for(node neighbor : neighbors){
            if(neighbor.name.equals(arg_name)){
                return true;
            }
        }
        return false;
    }

    //add neighrs 
    public void addneighbors(node arg_node){
        //if list is empty, just add it
        if(neighbors.isEmpty()){
            neighbors.add(arg_node);
            return;
        }

        //add before if it's smaller than the one you're checking and end the function
        for(int i = 0; i < neighbors.size(); i++){
            if(arg_node.name.charAt(0) <= neighbors.get(i).name.charAt(0)){
                neighbors.add(i, arg_node);
                return;
            }
        }
        
        //add to the end if nothing is found
        neighbors.add(arg_node);
    }
    
    //remove links of the neighbor
    public void removeneighbors(node arg_node){
        if(neighbors.isEmpty()){
            return;
        }
        neighbors.remove(arg_node);
    }

    //function to print neighbors, used for checking graph
    public void printNeighbors(){
        System.out.println(name+"'s neighbors:");
        for(node neighbor : neighbors){
            System.out.println("- "+ neighbor.name);
        }
    }

}

class Graph{
    private node Vertices[]; //variable containing all the vertices
    private int vertex_count; //counter to keep track of how many we have filled in the array
    
    //constructor, set the size only
    public Graph(){
        vertex_count = 0;
    }
    
    //set the size of the array and initialize all the objects
    public void setSize(int arg_size){
        this.Vertices = new node[arg_size];
        for (int i = 0; i < arg_size; i++){
            Vertices[i] = new node();
        }
    }
    
    //returns the size of the array
    public int getSize(){
        return vertex_count;
    }

    //returns true if the graph is empty
    public boolean isEmpty(){
        return vertex_count == 0;
    }

    //boolean function that returns true if the name already exists in the vertices array
    public boolean contains(String arg_name){
        if(isEmpty()){
            return false;
        }
        for(int i = 0; i < vertex_count; i++){
            if (Vertices[i].name.equals(arg_name)){
                return true;
            }
        }
        return false;
    }
    
    //function to return the index of the vertices with the name
    public int indexof(String arg_name){
        int counter = 0;
        while(!(Vertices[counter].name.equals(arg_name))){
            counter++;
        }
        return counter;
    }
    public void add(String arg_name){

        if(!contains(arg_name)){ //check to see if it exists

            //set the name for the vertices
            Vertices[vertex_count].setName(arg_name);

            //increment vertices counter
            vertex_count++;
        }

    }

    public void addfriendship(String arg_name1, String arg_name2){
        //check if they exist first, if not then make them
        add(arg_name1);
        add(arg_name2);
        
        //add links to the friendship by connecting the nodes in their both neighbors list
        Vertices[indexof(arg_name1)].addneighbors(Vertices[indexof(arg_name2)]);
        Vertices[indexof(arg_name2)].addneighbors(Vertices[indexof(arg_name1)]);
    }


    public void removefriendship(String arg_name1, String arg_name2){
        //find both vertices with the matching names and remove eachother from their list

        Vertices[indexof(arg_name1)].removeneighbors(Vertices[indexof(arg_name2)]);
        Vertices[indexof(arg_name2)].removeneighbors(Vertices[indexof(arg_name1)]);
        
    }

    public void BFS(String arg_source, String arg_destination){
        boolean pathFound = false; //flag for path found
        LinkedList<node> queue = new LinkedList<node>(); //queue for BFS
        LinkedList<node> path = new LinkedList<node>(); //list to save the path
        HashMap<node, Boolean> visited = new HashMap<node, Boolean>(); //hashmap for visited nodes
        HashMap<node, node> parents = new HashMap<node, node>();

        for(node vertex : Vertices){ //initialize all values to false;
            visited.putIfAbsent(vertex, false);
        }

        //add to queue
        queue.addLast(Vertices[indexof(arg_source)]);

        while(!(queue.isEmpty()) && !pathFound){
            //dequeue
            node v = queue.removeFirst();

            //mark visited
            if(!visited.get(v)){
                visited.put(v, true);
                path.add(v);

                //check all the neighers
                for(node neighbor : v.getNeighbors()){
                    parents.putIfAbsent(neighbor, v); //map the nodes to parents to save the route

                    if(!visited.get(neighbor)){//if not visited, add to queue
                        queue.addLast(neighbor);
                    }
                    
                    //if path is found then get out.
                    if (neighbor.name.equals(arg_destination)){
                        path.add(neighbor);
                        backtrack(parents ,path, arg_source);
                        pathFound = true;
                        break;
                    };
                }
            }
        }
        output(pathFound, path, arg_destination); //format output
    }

    //function to print out the output
    public void output(boolean arg_found, LinkedList<node> arg_path, String arg_destination){
        //if found print the output
        if (arg_found){
            System.out.println(" - Length of the shortest path: " + (arg_path.size()-1));

            if(arg_path.size() > 3){
                System.out.println(" - Your intermediate friend is " + arg_path.get(1).name);
            }
            else {
                System.out.println(" - Your mutual friend is " + arg_path.get(1).name);
            }

            System.out.print(" - Path: ");
            for(node direction : arg_path){
                System.out.print(direction.name + " ");
            }
            System.out.println();
            }
        else { //if no path then cry.
            System.out.println(" - Sorry, none of your friends can help introduce you to " + arg_destination + ".");
        }
    }

    //backtracking function to filter out the unnecessary nodes
    public void backtrack(HashMap<node, node> arg_parents, LinkedList<node> path, String arg_source){
        int index = 2;
        node current = path.getLast();
        node parent;

        //backtrack and remove any parents not in the sequence of the route
        while(index <= path.size()){
            parent = path.get(path.size()-index);

            if(!(arg_parents.get(current).equals(parent))){
                path.remove(parent);
            }
            else {
                current = parent;
                index++;
            }
        }
     
    }

    //print vertices and their neighbors
    public void printvertices(){
        for(node vertex : Vertices){
            System.out.println(vertex.name);
            vertex.printNeighbors();
        }
    }

}

class hw6{

    public static void readFriends(String arg_filename, Graph arg_friendlist) {
        try(BufferedReader file = new BufferedReader(new FileReader(arg_filename))) {

            String line; //line for reading line in a file
            String words[]; //words in the line
            while ((line = file.readLine()) != null) {
                words = line.split(" ");

                if (words.length == 1) {
                    arg_friendlist.setSize(Integer.parseInt(words[0]));
                    continue;
                }
                else {
                    arg_friendlist.addfriendship(words[0], words[1]);                }
            }
            file.close();
        }
        catch (FileNotFoundException exception){ //exception just for files
            System.out.println(exception);
        }
        catch (IOException exception){ //exception if anything else goes wrong, just a habit.
            System.out.println(exception);
        }
    }

    public static void readActions(String arg_filename, Graph arg_friendslist) {
        try(BufferedReader file = new BufferedReader(new FileReader(arg_filename))) {
            String line; //line for reading line in a file
            String words[]; //words in the line
            while ((line = file.readLine()) != null) {
                words = line.split(" "); //split the words and parse
                System.out.println(line);
                parseCommands(words, arg_friendslist);
            }
            file.close();
        }
        catch (FileNotFoundException exception){ //exception just for files
            System.out.println(exception);
        }
        catch (IOException exception){ //exception if anything else goes wrong, just a habit.
            System.out.println(exception);
        }
    }

    public static void parseCommands(String arguments[], Graph arg_friendslist){
        switch(arguments[0]) { //do the functions to specified to each commands
            case "WantToBefriend":
            arg_friendslist.BFS(arguments[1], arguments[2]);
            break;

            case "AddFriendship":
            arg_friendslist.addfriendship(arguments[1], arguments[2]);
            break;

            case "RemoveFriendship":
            arg_friendslist.removefriendship(arguments[1], arguments[2]);
            break;

            default:
            System.out.println("Invalid command.");
            break;
        }
    }
    
    public static void main(String args[]){
        Graph friendslist = new Graph();
        
        readFriends(args[0], friendslist);
        readActions(args[1], friendslist);

    }
}