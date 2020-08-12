package near;

public class History
{
    protected String writeHistory;
    protected Integer carHistory;
    protected Double scrollTopHistory, scrollLeftHistory;

    public History( String string, Integer integer, Double number1, Double number2 )
    {
            writeHistory = string;
            carHistory   = integer;
            scrollTopHistory  = number1;
            scrollLeftHistory = number2;
    }
    
    public String getText() { return writeHistory; }
    
    public Integer getCar() { return carHistory;   }
    
    public Double getTopScroll()  { return scrollTopHistory;  }
    
    public Double getLeftScroll() { return scrollLeftHistory; }
}