#include<iostream>
using namespace std;
class SparseRow {
    protected:
        int row; //Row#
        int col; //Column#
        int value; //We will assume that all our values will be integers
    public:
        SparseRow (){
            //default constructor; row=-1;col=-1;value=0
            row = -1;
            col = -1;
            value = 0;
        }
        //display(); // print Row#, Column#, value
        //other methods that are necessary such as get and set
        void setRow(int r){
            row = r;
        }
        void setColumn(int c){
            col = c;
        }
        void setValue(int val){
            value = val;
        }
        int getRow(){
            return row;
        }
        int getColumn(){
            return col;
        }
        int getValue(){
            return value;
        }
};
class SparseMatrix {
    protected:
        int noRows; //Number of rows of the original matrix
        int noCols; //Number of columns of the original matrix
        int commonValue; //read from input
        int noNonSparseValues;

    public:
        SparseRow* myMatrix; //Array
        SparseMatrix ();
        SparseMatrix (int n, int m, int cv, int noNSV);
        SparseMatrix* Transpose (); //Matrix Transpose
        SparseMatrix* Multiply (SparseMatrix& M);
        SparseMatrix* Add (SparseMatrix& M);
        void display();//Display the sparse matrix
        void displayMatrix (); //Display the matrix in its original format
        //other methods that are necessary such as get and set
};
SparseMatrix::SparseMatrix (int n, int m, int cv, int noNSV) {
    noRows = n;
    noCols = m;
    commonValue = cv;
    noNonSparseValues = noNSV;
    myMatrix = new SparseRow[noNSV];
}

void SparseMatrix::display(){

    for (int k = 0; k < noNonSparseValues; k++)
    {
        if (myMatrix[k].getValue() != commonValue)
        {
            cout<< myMatrix[k].getRow() << ", "<< myMatrix[k].getColumn()
                                        <<", "<< myMatrix[k].getValue()<<endl;
        }
    }
}

void SparseMatrix::displayMatrix(){
   int val, k;
   for(int i=0; i < noRows ; i++){
            for(int j=0; j < noCols; j++){
                val=commonValue;
                k=0;
                while(k<noNonSparseValues){
                    if(myMatrix[k].getRow()==i && myMatrix[k].getColumn()==j){
                        val= myMatrix[k].getValue();
                    }
                    k++;
                }
                cout<<val <<" ";
            }
            cout << endl;
    }
}
SparseMatrix* SparseMatrix::Multiply (SparseMatrix& M)
{
    if (M.noCols != noRows)
    {
        cout << "Multiplication of matrices is not possible" << endl;
    }
    int arraySize = noCols * M.noRows;
    SparseMatrix* temp = new SparseMatrix(noRows,noCols,commonValue,arraySize);
    int X = 0,Y=0,Z=0, value1 = M.commonValue, value2 = commonValue, value3 = 0;
    for (int i = 0; i < noRows; i++)
    {
        for (int j = 0; j < M.noCols; j++)
        {
            for (int k = 0; k < noCols; k++)
            {
                value1 = commonValue;
                value2 = M.commonValue;
                X = 0; Y = 0;
                while (X < noNonSparseValues)
                {
                    if ((myMatrix[X].getRow() == i) && (myMatrix[X].getColumn() == k))
                    {
                        value1 = myMatrix[X].getValue();
                        break;
                    }

                    X++;
                }

                while (Y < M.noNonSparseValues)
                {
                    if ((M.myMatrix[Y].getRow() == k) && (M.myMatrix[Y].getColumn() == j))
                    {
                        value2 = M.myMatrix[Y].getValue();
                        Y++;
                        break;
                    }
                    Y++;
                }
                value3 += value1 * value2;
            }
            if (Z < arraySize && value3 != commonValue)
            {
                (*temp).myMatrix[Z].setRow(i);
                (*temp).myMatrix[Z].setColumn(j);
                (*temp).myMatrix[Z].setValue(value3);
                value3=0;
                Z++;
            }
            (*temp).noNonSparseValues = Z;
        }
    }
    return temp;
}

SparseMatrix* SparseMatrix::Transpose()
{
    SparseMatrix* temp = new SparseMatrix(noCols,noRows,commonValue,noNonSparseValues);
    int k=0;
    while(k<noNonSparseValues){
        (*temp).myMatrix[k].setValue(commonValue);
        (*temp).myMatrix[k].setRow(myMatrix[k].getColumn());
        (*temp).myMatrix[k].setColumn(myMatrix[k].getRow());
        (*temp).myMatrix[k].setValue(myMatrix[k].getValue());
        k++;
    }
    return temp;
}

SparseMatrix* SparseMatrix::Add (SparseMatrix& M)
{
    int k1 = 0,k2 = 0, k3 = 0, value1 = 0, value2 = 0, value3 = 0, arraySize = noNonSparseValues +  M.noNonSparseValues;
    SparseMatrix* temp = new SparseMatrix(noRows, noCols, commonValue, arraySize);
    for (int i = 0; i < noRows; i++)
    {
        for (int j = 0; j < noCols; j++)
        {
            value1 = value2 = commonValue;
            if ((myMatrix[k1].getRow() == i) && (myMatrix[k1].getColumn() == j))
            {
                value1 = myMatrix[k1].getValue();
                k1++;
            }
            if ((M.myMatrix[k2].getRow() == i) && (M.myMatrix[k2].getColumn() == j))
            {
                value2 = M.myMatrix[k2].getValue();
                k2++;
            }
            value3 = value1+value2;
            if ((k3 < arraySize) && value3 != commonValue)
            {
                (*temp).myMatrix[k3].setRow(i);
                (*temp).myMatrix[k3].setColumn(j);
                (*temp).myMatrix[k3].setValue(value3);
                k3++;
            }
            value3 = 0;
        }
    }
    return temp;
}

int main()
{
    int n, m, cv, noNSV;
    SparseMatrix* temp;
    cin >> n >> m >> cv >> noNSV;
    SparseMatrix* firstOne = new SparseMatrix(n,m,cv,noNSV);
    //Write statements to read in the first matrix
    int val = 0, k = 0;
    for (int i=0; i < n; i++) {
        for (int j=0; j < m; j++) {
            if(k >= n * m)
            {
                    break;
            }
            cin >> val;
            if (val != cv)
            {
                (*firstOne).myMatrix[k].setRow(i);
                (*firstOne).myMatrix[k].setColumn(j);
                (*firstOne).myMatrix[k].setValue(val);
                k++;
            }
        }
    }
    cin >> n >> m >> cv >> noNSV;
    SparseMatrix* secondOne = new SparseMatrix(n,m,cv,noNSV);
    //Write statements to read in the second matrix
    val = 0;k=0;
    for (int i=0; i < n; i++) {
        for (int j=0; j < m; j++) {
            if(k >= n*m)
            {
                    break;
            }
            cin >> val;
            if (val != cv)
            {
                (*secondOne).myMatrix[k].setRow(i);
                (*secondOne).myMatrix[k].setColumn(j);
                (*secondOne).myMatrix[k].setValue(val);
                k++;
            }
        }
    }
    cout << "First one in sparse matrix format " << endl;
    (*firstOne).display();

    cout << "First one in normal matrix format" << endl;
    (*firstOne).displayMatrix();

    cout << "Second one in sparse matrix format" << endl;
    (*secondOne).display();
    cout << "Second one in normal matrix format" << endl;
    (*secondOne).displayMatrix();

    cout << "After Transpose first one in normal format" << endl;

    temp = (*firstOne).Transpose();

    (*temp).displayMatrix();

    cout << "After Transpose second one in normal format" << endl;
    temp = (*secondOne).Transpose();
    (*temp).displayMatrix();

    cout << "Multiplication of matrices in sparse matrix form:" << endl;
    temp = (*secondOne).Multiply(*firstOne);
    (*temp).display();
    cout << "Addition of matrices in sparse matrix form:" << endl;
    temp = (*secondOne).Add(*firstOne);
    (*temp).display();

    delete firstOne;
    delete secondOne;

    return 0;
}
