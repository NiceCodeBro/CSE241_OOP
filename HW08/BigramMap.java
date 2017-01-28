/*
	 This class uses STL Map class to implement functions. 
	 a class hierarchy for bigrams (2-Gram). A bigram is a specialization 
	 of N-Gram which “is a contiguous sequence of N items from a given data sequence”.
*/
import java.io.*;
import java.util.*;
import java.util.Scanner;

/**
 *
 * @author MSD
 * @param <T>
 */
public class BigramMap<T> implements Bigram<T>{
    protected int dataType; //means 1 for int, 2 for strings, 3 for doubles
    protected int count; //number of element from file (123 3244 22 means count=3) 
    protected Map mymap;
    protected String fileName;
    
    public BigramMap() { count = 0; }
    public BigramMap(int dataT) { dataType = dataT; count = 0; }
    //getter and setters
    public int getDataType() {return dataType;}
    public int getCount() {return count;}
    public void setCount(int newCount) { count = newCount;}
    public void setFileName(String name) { fileName = name; }
    public String getFileName() { return fileName; }
    
    //returns the total number of bigrams calculated so far.
    @Override
    public int numGrams() 
    {
        if(count>0)
            return count-1;
        else
            return 0;
    }

	//takes two elements as bigrams and returns the number of that bigram read so far.
    @Override
    public int numOfGrams(T var1, T var2){
        Iterator it = mymap.entrySet().iterator();
        String temp = var1.toString() + "=" + var2.toString();

        while (it.hasNext()) {
            Map.Entry pair = (Map.Entry)it.next();
            if(pair.getKey().toString().equals(temp)){
                return (int)pair.getValue();
            }
        }
        return 0;
    }
    //return of all pairs and pairs's counts
    @Override
    public String toString()
    {    

        String [] tempArr = new String[mymap.size()];
        int [] counter = new int[mymap.size()];
	int a=0;

        for(int i = 0; i < mymap.size(); ++i) counter[i] = 0;
   
    Iterator it = mymap.entrySet().iterator();
    while (it.hasNext()) {
        
        Map.Entry pair = (Map.Entry)it.next();
        tempArr[a] = pair.getKey().toString();
        counter[a] = (int)pair.getValue();
        ++a;
    }
    
    for(int i = 0; i < a - 1; i++)
    {
        for(int j = i + 1; j < a; j++)
        {
            if( counter[i] < counter[j] )
            {
                String tempVar1 = tempArr[i];
                int tempCount = counter[i];
                
                tempArr[i] = tempArr[j];
                counter[i] = counter[j];
                
                tempArr[j] = tempVar1;
                counter[j] = tempCount; 
            }
        }
    }
    String temp="";
    for(int i = 0; i < a ; ++i)
    {
        String[] temp2= tempArr[i].split("=");
        temp = temp + "[" + temp2[0] + ", " + temp2[1] + "] = " + counter[i] ;
        if(i<a-1) temp = temp + "\n";
    }
    return temp;
   }
    //read file, check error case and throw exceptions for that and fill key class array
    @Override
    public void readFile(String fileName)  throws myException
    { 
        T temp1, temp2;
        mymap = new HashMap();
        setFileName(fileName);

        if(checkBadData() == -1)
        {
            throw new myException("Bad data error!");
        }
        if(getCount() <= 1)
        {
            throw new myException("File has insufficient staff!");
        }
        Scanner inp;
        try {
            inp = new Scanner(new File(fileName));
        } catch (FileNotFoundException e) {
            throw new myException("Can't open the file !");
        }
            temp1 = (T)inp.next();
            while(inp.hasNext())
            {
                temp2 = (T)inp.next();
                My_Pair <T,T> myPair = new My_Pair <>(temp1,temp2);
               if(!mymap.containsKey(myPair))
                    mymap.put(myPair, 1);
               else
                   mymap.put(myPair, (int)mymap.get(myPair)+1);

                temp1 = temp2;
            }    
    }
    //method check if string only contain numbers, convert integer
    public int stringToInteger(String var) 
    {
        int number=0;
        for(int i=0; i < var.length(); ++i)
        {
            if(var.charAt(i) >= '0' && var.charAt(i) <= '9')
            {
                number = number * 10;
                number = number + (var.charAt(i)-'0');
            }
            else    
                return -1;
        }
        return number;
    }
	//check @param1 contain only double else return -1
    public double stringToDouble(String var) 
    {
        int indicator=0;
        for(int i=0; i < var.length(); ++i)
        {
            if((var.charAt(i)>='0' && var.charAt(i)<='9') || var.charAt(i)=='.')
            {
                if(var.charAt(i)=='.' && i!=var.length()-1 && var.charAt(0)!='.') ++indicator;
            }
            else 
                return -1;
        }
        if(indicator!=1) return -1; //string contain more than one dot

        return Double.parseDouble(var);
    }
    //if read word equal int or double or string, Then others words should be equal to it
    public int checkBadData() throws myException
    { 
        Scanner input;
        try {
            input = new Scanner(new File(fileName));
        } catch (FileNotFoundException ex) {
            throw new myException("Can't open the file !");
        }        
            String temp;
            while(input.hasNext())
            {      
               temp = input.next();
                setCount( getCount() + 1 );
                if(getDataType() == 1 && stringToInteger(temp)==-1 )
                {
                    return -1;
                }  
                else if(getDataType() == 3 && stringToDouble(temp)==-1 )
                {
                    return -1;
                }     
            }
        return 0;   
    }
}
