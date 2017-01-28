/*
	This header simulate java map class
*/
/**
 *
 * @author MSD
 * @param <T>
 */
public class KeyC<T> {

    protected T first, second; //key1 and key2
    protected int number; // number of occurance of key pairs
    protected int dataType; //means 1 for int, 2 for strings, 3 for doubles   
    //constructors
    public KeyC(){ number = 0; }
    public KeyC(T var1, T var2)
    {
        this.first = var1;
        this.second = var2;
        this.number = 0;
    }
    public KeyC( KeyC var)
    {
        this.first=(T) var.first;
        this.second=(T) var.second;
        this.number = var.number;
        this.dataType = var.dataType;
    }
    public void setKeyToKey(KeyC other) {
        this.first = (T) other.first;
        this.second = (T) other.second;
        this.number = other.number;
        this.dataType = other.dataType;  
    };
   
    @Override
    public String toString(){ return "["+getFirst()+", " + getSecond() + "]";}
    //getters 
    public T getFirst()  {return first;}
    public T getSecond()  {return second;}
    public int getNumber()  {return number;}
    public int getDataType()  { return dataType;}
    //setters
    public void setKeys( T var1,  T var2)  { first = var1; second = var2;}
    public void setNumber( int num) { number = num; }
    public void setDataType( int dType) { dataType = dType; }
    public void setFirstSecond( T var1,  T var2) { first = var1; second = var2; }
}



  
