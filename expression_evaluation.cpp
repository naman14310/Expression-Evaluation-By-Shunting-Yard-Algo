#include<iostream>
using namespace std;

template <class T>
 
class mystack {

        struct node {
            T data;
            node* next;
        };

        node* top;

    public:
        mystack(){
            top = NULL;
        }

        void push(const T &item){
            node* N = new node;
            N->data = item;
            N->next = top;
            top = N;
        }

        void pop(){
            node* p = top;
            top = top->next;
            delete p;
        }

        bool isEmpty(){
            if(top==NULL) return true;
            else return false;
        }

        void printAll(){
            node* tmp = top;

            while(tmp){
                cout<<tmp->data<<" ";
                tmp = tmp->next;
            }
            cout<<endl;
        }

        T Top(){
            node* tmp = top;
            return tmp->data;
        }

        int precedence(char op){
            if(op=='*' || op=='/' || op=='%') return 2;
            else if(op=='+' || op=='-') return 1;
            else return 0;
        }

        bool chkPrecedence(char op, char t){
            if(precedence(t)>=precedence(op)) return true;
            else return false;
        }

};



double operation(double a, double b, char op){
    
    if(op=='+'){
        return a+b;
    }
    else if(op=='-'){
        return a-b;
    }
    else if(op=='*'){
        return a*b;
    }
    else if(op=='/'){
        return a/b;
    }
    else if(op=='%'){
        return (int)a % (int)b ;
    }

    return 0;
}

double evaluate(string expression){
    mystack<char> opStack;
    mystack<double> valStack;

    for(int i=0; i<expression.size(); i++){

        if(isdigit(expression[i]) || expression[i]=='.'){
           // cout<<"hit num"<<endl;
            string temp = "";
            while( (isdigit(expression[i]) || expression[i]=='.') && i<expression.size() ){
                
                temp.push_back(expression[i]);
                i++;

                if(i==expression.size()) break;
            }
            i--;
            double ip = stod(temp);
            valStack.push(ip);
        }

        else if(expression[i]=='('){
            opStack.push('(');
            //cout<<"hit open brac"<<endl;
        }

        else if(expression[i]==')' ){
           // cout<<"hit close brac"<<endl;
            while( opStack.Top() != '(' && opStack.isEmpty()==false){

                char op = opStack.Top();
                opStack.pop();

                double ip2 = valStack.Top();
                valStack.pop();

                double ip1 = valStack.Top();
                valStack.pop();

                double res = operation(ip1, ip2, op);

                valStack.push(res);
            }

            if(opStack.isEmpty()==false) opStack.pop();

        }

        else{
           // cout<<"hit op"<<endl;
            char op1 = expression[i];
           // cout<<"Chk 1------------                      "<<op1<<endl;
            if(opStack.isEmpty()==false){
                char op2 = opStack.Top();
              //  cout<<"Chk 2------------                      "<<op2<<endl;

                //cout<<"hello";
                bool perform = opStack.chkPrecedence(op1, op2);

               // cout<<"hiiiiiiiiiii";

                /*if((op1=='*' || op1=='/' || op1=='%' ) && (op2=='*' || op2=='/' || op2=='%' )){
                    perform = true;
                }
                else if((op1=='+' || op1=='-' ) && (op2=='*' || op2=='/' || op2=='%' )){
                    perform = true;
                }
                else if((op1=='+' || op1=='-') && (op2=='+' || op2=='-' )){
                    perform = true;
                }*/
                
                //cout<<"hiiiiiiiiiii";
                while(opStack.isEmpty()==false && perform){

                    opStack.pop();

                    double ip2 = valStack.Top();
                    valStack.pop();

                    double ip1 = valStack.Top();
                    valStack.pop();

                    double res = operation(ip1, ip2, op2);

                    valStack.push(res);

                    if(opStack.isEmpty()==true) break;
                    
                    op2 = opStack.Top();

                    if((op1=='*' || op1=='/' || op1=='%' ) && (op2=='-' || op2=='+')){
                        perform = false;
                    }   
                    // perform = precedence(op2)>=precedence(op1) ? true : false;
                    perform = opStack.chkPrecedence(op1, op2);
                }
            }

            opStack.push(op1);

        }

        //cout<<"ops : ";opStack.printAll();
        //cout<<"vls : ";valStack.printAll();
        //cout<<"****************";
    }

    while(opStack.isEmpty()==false){
        char op = opStack.Top();
         opStack.pop();

        double ip2 = valStack.Top();
        valStack.pop();

        double ip1 = valStack.Top();
        valStack.pop();

        double res = operation(ip1, ip2, op);

        valStack.push(res);

       // cout<<"ops : ";opStack.printAll();
       // cout<<"vls : ";valStack.printAll();
       // cout<<"*****************";
    }


    return valStack.Top();
}

int main(){
  
    string expr;

    cin>>expr;

    cout<<evaluate(expr)<<endl;

    return 0;

}