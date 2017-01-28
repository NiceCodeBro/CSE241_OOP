/*
	This header simulate java pair class
*/
public class My_Pair<T, Z>
{
    protected T l_pair;
    protected Z r_pair;
    public My_Pair(T var1, Z var2){ l_pair = var1;  r_pair = var2; }
    public T Left()   {  return l_pair;   }
    public Z Right()  {  return r_pair;   } 
 	public int hashCode() {	return l_pair.hashCode() ^ r_pair.hashCode();  }
    public String toString() { return  l_pair + "=" + r_pair;  }
    public boolean equals(Object o){
        My_Pair tempPair = (My_Pair) o;
        return l_pair.equals(tempPair.Left()) &&
        	   r_pair.equals(tempPair.Right());
    }
}
