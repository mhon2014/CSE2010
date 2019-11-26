/*
  Author: Michael Hon
  Email: mhon2014@my.fit.edu
  Course: CSE2010
  Section: E4
  Description: HW3 Java N-ary tree implementation.

 */
import java.util.Scanner;
import java.util.LinkedList;
import java.io.*;

//class node with stirng, parent node and list of children.
class node{
    public String category; //name of the node
    public node parent; // parent of the node with a class type node
    public LinkedList<node> children;  //list of childrent
    
    //constructor for node given the string name
    node(String arg_string){
        this.category = arg_string;
        this.parent = null;
        this.children = new LinkedList<node>();
    }

    //constructor for node given the string name and the node of the parent
    node(node arg_parent, String arg_string){
        this.category = arg_string;
        this.parent = arg_parent;
        this.children = new LinkedList<node>();
    }
}

// class tree object used for the tree with a root and the node_count
class Tree{
    private int node_count; //number of nodes in the tree
    private node root;

    //tree constructor to initialize the tree as empty
    Tree(){
        this.node_count = 0;
        this.root = null;
    }

    //get size function from tree
    public int size(){
        return this.node_count;
    }

    //get root of the tree.
    public node getRoot(){
        return this.root;
    }

    //get parent function of argument that's passed
    public node getParent(node arg_node){
        return arg_node.parent;
    }

    //return the list of children of argument passed
    public LinkedList<node> getChild(node arg_node){
        return arg_node.children;
    }

    //function just to check to see if tree is empty
    public boolean isEmpty(){
        if(this.node_count == 0) {
            return true;
        }
        else {
            return false;
        }
    }

    //helper function that just enqueues the list of children.
    public void addChildHelper(node arg_parent,LinkedList<node> arg_parent_child, LinkedList<String> arg_children){
        for(int i = arg_children.size(); i > 0 ; i--){
            //popping from the list of STRINGS and then enqueue with the node constructor in the list of NODES with the popped string
            arg_parent_child.add(new node(arg_parent, arg_children.removeFirst()));
            this.node_count++;
        }
    }

    //pass a string and a list of string children in alphabetical order
    public void addChild(String arg_parent, LinkedList<String> arg_children){
        /*
        if the tree is empty then make a new root with the string passed and set the children.
        
        else, find the node that contains the same string and then set the children
        */
        if (this.isEmpty()) {
            this.root = new node(arg_parent);

            this.addChildHelper(this.getRoot(), getChild(this.getRoot()), arg_children);

            this.node_count += 1;
        }
        else {
            node found = search(this.getRoot(), arg_parent);
            this.addChildHelper(found, getChild(found), arg_children);
        }
    }

        
    //recursive function to traverse the tree and return the node if it is found, else return null
    public node search(node arg_parent, String arg_category){
        if (arg_parent.category.equals(arg_category)){
            return arg_parent;
        }
        else {
            for (node child: getChild(arg_parent)) {
                node temp = search(child, arg_category);
                if (temp != null){
                    return temp;
                }
            }
        }
        return null;
    }

    //recursive functions that adds to a list sequence the pre order traversal of a certain node
    public void pre_order(node arg_parent, LinkedList<String> arg_sequence){
        for (node child: getChild(arg_parent)) {
            arg_sequence.add(child.category);
            pre_order(child, arg_sequence);
        }
    }

    //recursive function to count the number of nodes starting from the arguments node to all it's children
    public int count_node(node arg_parent){
        int number_of_subcats = 1;
        for (node child: getChild(arg_parent)) {
            number_of_subcats += count_node(child);
        }
        return number_of_subcats;
    }

    //get the depth of a node by finding it first and then counting the parents till null
    public int getDepth(String arg_category) {
        int depth = 0;
        node temp = this.search(this.getRoot(),arg_category);
        while(temp.parent != null){
            temp = temp.parent;
            depth++;
        }
        return depth;
    }

    //just return the parent of the node
    public String DirectSupercategory(String arg_category) {
        return this.getParent(this.search(this.getRoot(),arg_category)).category;
    }

    //find the node and then make a string array of all the direct children to be printed out
    public String[]  DirectSubcategories(String arg_category){
        node temp = this.search(this.getRoot(),arg_category);
        String[] subcategories = new String[getChild(temp).size()];
        for(int i = 0; i < getChild(temp).size(); i++){
            subcategories[i] = getChild(temp).get(i).category;
        }
        return subcategories;
    }

    //find the node and then traverse up all the way null, add each string to an array and return it.
    public String[]  AllSupercategories(String arg_category){
        int depth = this.getDepth(arg_category);
        node temp = this.search(this.getRoot(), arg_category);
        String[] supercategories = new String[depth];
        for(int i = 0; i < depth; i++) {
            temp = temp.parent;
            supercategories[i] = temp.category;
        }
        return supercategories;
    }
   
    //do preorder traversal at a node and just return the elements in the list to be printed.
    public LinkedList<String> AllSubcategories(String arg_category){
        node temp = this.search(this.getRoot(), arg_category);
        LinkedList<String> allsubcategories = new LinkedList<String>();
        pre_order(temp, allsubcategories);
        return allsubcategories;

    }
    
    //use the getdepth function to return the depth
    public int  NumberOfAllSupercategories(String arg_category){
        return this.getDepth(arg_category);
    }

    //call the recursive node count to get the number of all subcategories
    public int NumberOfAllSubcategories(String arg_category){
        return this.count_node(search(this.getRoot(), arg_category))-1;
    }
    
    //just compare if the two arguments' node have a relationship
    public String IsSupercategory(String arg_category, String arg_supercategory){
        node temp = this.search(this.getRoot(), arg_category);
        while (temp.parent != null) {
            temp = temp.parent;
            if (temp.category.equals(arg_supercategory)){
                return "yes";
            }
        }
        return "no";
    }

    //just compare if the two arguments' node have a relationship
    public String  IsSubcategory(String arg_category, String arg_subcategory){
        node temp = search(this.getRoot(), arg_category);
        LinkedList<String> allsub = new LinkedList<String>();
        pre_order(temp, allsub);
        for(String subs: allsub){
            if(subs.equals(arg_subcategory)){
                return "yes";
            }
        }
        return "no";
    }

    /*
    make 2 arrays of the common supercategories and compare them if one of them equals the other,
    would've been easier to use intersection with sets
    but I just brute forced it.
    */
    public String ClosestCommonSupercategory(String arg_category1, String arg_category2){
        String[] common_cat_one = AllSupercategories(search(this.getRoot(), arg_category1).category);
        String[] common_cat_two = AllSupercategories(search(this.getRoot(), arg_category2).category);

        for(String names_one: common_cat_one) {
            for (String names_two:common_cat_two){
                if (names_one.equals(names_two)) {
                    return names_one;
                }
            }
        }
        
        return null;

    }

}
class HW3{
    public static void main(String[] args){
        Tree treeObject = new Tree();

        //try catch block to read the tree data and build the tree
        try(BufferedReader file = new BufferedReader(new FileReader(args[0]))) {
            //list used for dequeueing and getting the string and enqueueing the string into a list of nodes in the tree
            LinkedList<String> children = new LinkedList<String>();
            String line; //line for reading line in a file
            String[] words; //words in the line
            while ((line = file.readLine()) != null) {
                words = line.split(" ");
                for (String word : words){
                    /*
                    if it's the first word then just ignore it because we don't want to insert into tree
                    without knowing if there exist a node in there already.
                    */
                    if (word == words[0]){
                        continue;
                    }
                    /*
                    if else statements to enforce alpabetical order of the list
                    
                    #if child is empty, just add it
                    #else if check if it's smaller than first, add to beginning
                    #else if check if it's bigger than last, add to the end
                    #else loop through items to get a node where it's bigger, insert it after the node.

                    */
                    if (children.isEmpty()){
                        children.add(word);
                    }
                    else if(children.getFirst().charAt(0) > word.charAt(0)){
                        children.addFirst(word);
                    }
                    else if(children.getLast().charAt(0) < word.charAt(0)){
                        children.addLast(word);
                    }
                    else{
                        for(int i = 0; i < children.size(); i++){
                            if(children.get(i).charAt(0) < word.charAt(0)){
                                children.add(i+1, word);
                                break;
                            }
                        }
                    }
                }
                //call the add child function
                treeObject.addChild(words[0], children);
            }
            file.close();
        }
        catch (FileNotFoundException exception){ //exception just for files
            System.out.println(exception);
        }
        catch (IOException exception){ //exception if anything else goes wrong, just a habit.
            System.out.println(exception);
        }



        //try catch for reading the query arguments
        try(BufferedReader file = new BufferedReader(new FileReader(args[1]))) {
            String line;
            String[] words;
            while ((line = file.readLine()) != null) {
                words = line.split(" "); //array of all words in each line
                switch (words[0]) { //switch cases for all the queries
                    case "DirectSupercategory":
                        System.out.println(words[0] + " " + words[1] + " " + treeObject.DirectSupercategory(words[1]));
                        break;

                    case "DirectSubcategories": //use the directsubcategories function from the tree
                        String[] subcategories = treeObject.DirectSubcategories(words[1]);
                        System.out.print(words[0] + " " + words[1]);
                        for(String categories: subcategories){
                            System.out.print(" " + categories);
                        }
                        System.out.println();
                        break;

                    case "AllSupercategories": //use the AllSupercategories function from the tree
                        String[] supercategories = treeObject.AllSupercategories(words[1]);
                        System.out.print(words[0] + " " + words[1]);
                        for(String categories: supercategories){
                            System.out.print(" " + categories);
                        }
                        System.out.println();
                        break;

                    case "AllSubcategories": //use the AllSubcategories function from the tree
                        LinkedList<String> allsubcategories = treeObject.AllSubcategories(words[1]);
                        System.out.print(words[0] + " " + words[1]);
                        for(String categories: allsubcategories) {
                            System.out.print(" " + categories);
                        }
                        System.out.println();
                        break;

                    case "NumberOfAllSupercategories": //use the NumberOfAllSupercategories function from the tree
                        System.out.println(words[0] + " " + words[1] + " " + treeObject.getDepth(words[1]));
                        break;

                    case "NumberOfAllSubcategories": //use the NumberOfAllSubcategories function from the tree
                        System.out.println(words[0] + " " + words[1] + " " + (treeObject.NumberOfAllSubcategories(words[1])));
                        break;

                    case "IsSupercategory": //use the IsSupercategory function from the tree
                        System.out.println(words[0] + " " + words[1] + " " + words[2] + " " + treeObject.IsSupercategory(words[1], words[2]));
                        break;

                    case "IsSubcategory": //use the IsSubcategory function from the tree
                        System.out.println(words[0] + " " + words[1] + " " + words[2] + " " + treeObject.IsSubcategory(words[1], words[2]));
                        break;

                    case "ClosestCommonSupercategory": //use the ClosestCommonSupercategory function from the tree
                        System.out.println(words[0] + " " + words[1] + " " + words[2] + " " + treeObject.ClosestCommonSupercategory(words[1], words[2]));
                        break;
                }
            }
            file.close();
        }
        catch (FileNotFoundException exception){
            System.out.println(exception);
            }
        catch (IOException exception){
            System.out.println(exception);
        }
    }
}