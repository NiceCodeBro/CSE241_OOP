/*
The second class is BigramDyn which does not use
any STL classes or STL functions, it uses only old fashioned dynamic memory.

This header simulate that java map class using helper Key class
*/
import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

/**
 *
 * @author MSD
 * @param <T>
 */
public class BigramDyn<T> implements Bigram<T> {
    protected int count; //number of element from file (123 3244 22 means count = 3)
    protected int dataType; //means 1 for int, 2 for strings, 3 for doubles
    protected int keyUsed;
    protected KeyC<T>[] key = null ;
    protected String fileName;
    protected int loopVar;

	public BigramDyn(){count = 0; keyUsed = 0;   }
    public BigramDyn(int datatype){ dataType = datatype; } 
    //getter and setters
    public void setCount(int newCount) { count = newCount;}
    public int getCount() { return count; }
    public int getKeyUsed() { return keyUsed; }
    public KeyC<T> getKey(int index) { return key[index]; }
    public int getDataType() { return dataType; }
    public void setFileName(String name) { fileName = name; }
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
    @Override
    //read file, check error case and throw exceptions for that and fill key class array
    public void readFile( String fileName)  throws myException
    {
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

        key = new KeyC[count]; // allocating from memory
        
        for(int i = 0; i < count; ++i)
        { 
            key[i] = new KeyC();
            key[i].setDataType(dataType);
        }

       loopVar = 0;
        T temp1, temp2;

        temp1 = (T)inp.next();
        while(inp.hasNext())
        {
            temp2 = (T)inp.next();
            if(editKeyClassArray(temp1,temp2) == 1) 
                    key[loopVar].setFirstSecond(temp1, temp2);
            temp1 = temp2; 
        }
    }
    /*check our dynamic map exist pair(var1 and var2),if exist increase that index counter
	if not exist, add pair to end of key,sort by number of pair by decreasing order*/
    public int editKeyClassArray(T var1,T var2)
    {
        boolean flag = false;
        int whichIndex = 0;
        for(int i = 0; i < this.keyUsed; ++i)
        {	//check our dynamic map exist pair(var1 and var2)
            if(key[i].getFirst().toString().equals(var1.toString())  && 
                    key[i].getSecond().toString().equals(var2.toString())) 
            {
                flag = true; 
                whichIndex = i;
            }
        }

        if(flag == true) //if exist increase that index counter
        {
            key[whichIndex].setNumber(key[whichIndex].getNumber() + 1);
        }
        else // if not exist, add pair to end of key 
        {
            key[this.keyUsed].setKeys(var1, var2);
            key[this.keyUsed].setNumber(key[this.keyUsed].getNumber() + 1);
            ++this.keyUsed;
            ++loopVar;
        }

        //sort by number of pair by decreasing order
        for(int i = 0; i < count - 1; i++)
        {
            for(int j = i + 1; j < count; j++)
            {
                if(key[i].getNumber() < key[j].getNumber() )
                {
                    KeyC<T> tempKey = new KeyC<> () ;
                    tempKey.setKeyToKey(key[i]);
                    key[i] = key[j];
                    key[j] = tempKey;
                }
            }
        }

        if(flag == false)
            return 1;
        else
            return 0;
    }      

	//return of all pairs and pairs's counts
    public String toString() {
        String temp = "";
        for(int i = 0; i < this.keyUsed; ++i)
        {
            temp = temp + "[" + key[i].getFirst() + ", " + key[i].getSecond() + "] = " + key[i].getNumber();
            if(i != this.keyUsed - 1) temp = temp + "\n";
		}
        return temp;
    }
	
	@Override
	//returns the total number of bigrams calculated so far.
    public int numGrams() 
    {
        if(count > 0)
            return count-1;
        else
            return 0;
    }
	@Override
	//takes two elements as bigrams and returns the number of that bigram read so far.
    public int numOfGrams( T var1,  T var2) 
    {
        boolean flag = false;
        int index = 0;
        int i;
        
        for(i = 0; i < this.keyUsed; ++i)
        { 
            if(var1.toString().equals(key[i].getFirst().toString()) && 
                    var2.toString().equals(key[i].getSecond().toString()) )
            {  
                flag = true;
                index = i;
                i = this.keyUsed;
            }
        }
        
        if(flag == true)
            return key[index].getNumber();
        else
            return 0;
    }

}
