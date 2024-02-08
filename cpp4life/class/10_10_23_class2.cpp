#include <iostream>
#include <string>

void stringifyData(std::string& output, std::string input, std::string handledChar){    
    if (input!="0")
    {
        if (handledChar==" ")
        {
            if (output!="")
                {
                    if (input[0]=='-')
                    {
                        output += input;
                    }
                    else
                    {
                        output += ("+"+input);
                    }
                }
            else
            {
                output += input;
            }
        }
        else
        {
            if (input == "1")
            {
                output += handledChar;
            }
            else if(input == "-1")
            {
                output += ("-"+handledChar);
            }
            else
            {
                output += (input+handledChar);
            }
        } 
    }
}

int main(){
    std::string a,b;

    std::cin >> a >> b;

    std::string output = "";

    stringifyData(output,a,"x");
    stringifyData(output,b," ");
    
    if (output.size()==0)
    {
        std::cout << 0; 
    }
    else
    {
        std::cout << output; 
    }
}
