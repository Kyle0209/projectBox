#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;



class SingleItem{
public:
//	�i�f��;
	int date;
	int month;
	string donor; // ���ت�
	string itemName;
	string amount;
	string memo;

// �����	 
   string outMonth;
   string outDate;
   string recipient; // ����H


public:

	bool takenOut;
	
	SingleItem(){
		date = 0;
		month = 0;
		donor = "";
		itemName = "";
		amount = "";
		takenOut = false;

		outDate = "";
		outMonth = "";
		recipient = "";
	}
	
	SingleItem( int date, int month, string donor, string itemName, string amount ){
		this->date = date;
		this->month = month;
		if( donor == "00" ) this->donor.assign("������");
		else this->donor.assign(donor);
		this->itemName.assign(itemName);
		this->amount.assign(amount);
		this->takenOut = false;
		
		this->outDate = "";
		this->outMonth = "";
		this->recipient = "";
	}

	
	
	void setDate( int date) {
        this->date = date;
    }

	void setMonth(  int month){
		this->month = month;
	}

    void setDonor( string donor) {
        this->donor = donor;
    }

    void setItemName( string itemName) {
        this->itemName = itemName;
    }

    void setAmount(string amount) {
        this->amount.assign(amount);
    }
    
    void setOutDate( string outDate ){
    	this->outDate.assign(outDate);
	}
	
    void setOutMonth( string outMonth ){
    	this->outMonth.assign(outMonth);
	}
	
    void setRecipient( string recipient ){
    	this->recipient.assign(recipient);
	}
	
	void setTakenOut( bool takenOut ){
		this->takenOut = takenOut;
	}
	
	int getAmount_Int(){
		return stoi(amount);
	}
	
	string getAmount(){
		return amount;
	}
	
	string getDonor(){
		return donor;
	}
	
	int getDate(){
		return date;
	}

	int getMonth(){
		return month;
	}
	
	string getItemName(){
		return itemName;
	}
};

class SingleReceipt{
private:
	string barcode;

public:
	vector<SingleItem> list;

public:
	
	SingleReceipt( string barcode ){
		this->barcode.assign(barcode);
	}
	
	void displayReceipt(){
		cout << "--" << barcode << endl;
		for (auto& i : list) {
            cout << "----���: " << i.getMonth() << "��" << i.getDate() << "��" << "\t���ت�: " << i.getDonor() << "\t���~�W��: " << i.getItemName() << "\t�ƶq: " << i.getAmount() ;
			if(i.takenOut)
				cout << "\t����H:" << i.recipient << "\t���:" << i.outMonth << "\t��" << i.outDate << "��";
			cout << endl;
        }
		cout << endl;
	}
	void displayUntakenItem(){
		cout << barcode << endl;
		for (auto& i : list) {
			if( !i.takenOut ){
				cout << "���: " << i.getMonth() << "��" << i.getDate() << "��" << "\t���ت�: " << i.getDonor() << "\t���~�W��: " << i.getItemName() << "\t�ƶq: " << i.getAmount() << endl;
			}
		}
		cout << endl;
	}

	void takingOut(string outMonth, string outDate, string itemName, string recipient){
		for (auto& i : list) {
			if(i.itemName.compare(itemName) == 0){
				cout << i.itemName << endl;
				i.setTakenOut(true);
				i.setOutDate(outDate);
				i.setOutMonth(outMonth);
				i.setRecipient(recipient);
				break;
				
				cout << endl << i.itemName << " " << recipient << endl << endl;
			}
		}
	}
	
	string getBarcode(){
		return barcode;
	}

	int getListSize(){
		return list.size();
	}

	void addItem(int date, int month, string donor, string itemName, string amount){
		SingleItem temp(date, month, donor, itemName, amount);
		list.push_back(temp);
	}
	
	void popLast(){
		list.pop_back();
	}

	int itemSumming(){ // �^�ǥ��椤�Y�����~���ƶq *********
		return 0;
	};

	

	
	
};

class StockingSystem{
private:
	string fileName; // �g�ɦW��
	vector<SingleReceipt> stockList;  // �`�w�s 
	
public:
	
	void displayStockList(){
		for(auto i : stockList){
			i.displayReceipt();
		}
	}

	void displayUntakenList(){
		for( auto i : stockList){
			i.displayUntakenItem();
		}
	}
	
	// ����J�� 
	void doSingleIncome( string barcode ){ // �[�J�浧���ڤ��e 
		string donor, itemName;
		int date, month;
		string amount;
		SingleReceipt tempIncome(barcode);
		cout << "----���ت�(�Y�L��J\"00\"): " ;
		cin >> donor;
		cout << "----���(��): ";
		cin >> month ;
		cout << "----���(��): ";
		cin >> date ;
		cout << "----���~�W��: " ;
		cin >> itemName;
		while( itemName != "N" ){
			cout << "----�ƶq: ";
			cin >> amount ;
			cout << endl;
			
			tempIncome.addItem(date, month, donor, itemName, amount);
			
			cout << "--�R���W�@���п�J\"D\"\n----���~�W��(�Y���浲���п�J\"N\"): " ;
			cin >> itemName;
			while( itemName == "D" || itemName == "d" ){
				if( tempIncome.getListSize() == 0 ){
					cout << "\n--�������ڬ���\n" << endl;
					cout << "----��J���~�W��(�Y���浲���п�J\"N\"): " ;
				}
				
				else{
					tempIncome.popLast();
					cout << endl << "***�w�R���e�@���A�Э��s��J***"<< endl << endl; 
					cout << "--�R���W�@���п�J\"D\"\n----���~�W��(�Y���浲���п�J\"N\"): " ;
					
				}
				cin >> itemName;
			}
		}	
		
		stockList.push_back(tempIncome);
	}

	void doIncome(){ // �@���@����J���� 
		string barcode;
		cout << endl << "--�п�J���ڽs��(�Y�h�X��J�п�J\"N\"): ";
		cin >> barcode;
		while( barcode != "N" ){
			doSingleIncome(barcode);
			
			cout << endl << "--�п�J���ڽs��(�Y�h�X��J�п�J\"N\"): ";
			cin >> barcode;
		}
		cout << endl;
	}
	
	// �f����� 
	void doTakeOut(){ // �X�f�޿�?
		string barcode, itemName;
		string recipient, amount;
		string month, date;

		cout << "--unwritten function.\n" ; 
		displayUntakenList();
		cout << "--�п�J���ڽs��(�Y�h�X��J�п�J\"N\"): " ;
		cin >> barcode;
		while(barcode != "N"){
			cout << "----������:" ;
			cin >> month;
			cout << "----������:" ;
			cin >> date;
			cout << "----������~(�h�X��J\"N\"):";
			cin >> itemName;
			while( itemName != "N" && itemName != "n" ){
				cout << "----����H:";
				cin >> recipient;
				cin.ignore(); // �M������Ÿ�
				cout << endl;

				for( auto i : stockList ){
					if(i.getBarcode() == barcode){
						i.takingOut(month, date, itemName, recipient);
						break;
					}
				}
				cout << endl;
				cout << "----������~(�h�X��J\"N\"):";
				cin >> itemName;
			}


			cout << "--�п�J���ڽs��(�Y�h�X��J�п�J\"N\"): " ;
			cin >> barcode;
		}

		cout << "--�������" << endl << endl;
	}
	
	
	//�j�� 
	void searchByBarcode(){ // ��J���ڽs���A�C�X�Ҧ���T 
		string barcode;
		int index = 0;
		cout << "--�п�J���ڽs��(�Y�h�X��J�п�J\"N\"): ";
		cin >> barcode;
		for(const auto &receipt : stockList){
			if( stockList[index].getBarcode() == barcode ){
				stockList[index].displayReceipt();
				break;
			}
		}
		
		
	} 
	
	void searchByItem( string targetItem ){ // ��J���~�W�١A�C�X�Ҧ��ŦX���ƾ� 
		int total = 0;
		for(auto &searchReceipt : stockList){
			for(auto &searchItem : searchReceipt.list){
				if( searchItem.itemName == targetItem ){
					cout << endl; 
					cout << "--" << searchReceipt.getBarcode() << endl;
					cout << "----���: " << searchItem.getMonth() << "��" << searchItem.getDate() << "��" << "\t���ت�: " << searchItem.getDonor() << "\t���~�W��: " << searchItem.getItemName() << "\t�ƶq: " << searchItem.getAmount() ;
					if(searchItem.takenOut)
						cout << "\t����H:" << searchItem.recipient << "\t���:" << searchItem.outMonth << "\t��" << searchItem.outDate << "��";
					cout << endl;
				}
			}
		}
	}
	
	void searchByMonth( int month ){
		for(auto &searchReceipt : stockList){
			if(searchReceipt.list[0].month == month)
				searchReceipt.displayReceipt();
		}
	}
	
	void searchByDonor( string donorName ){
		for(auto &searchReceipt : stockList){
			if(searchReceipt.list[0].donor == donorName)
				searchReceipt.displayReceipt();
		}
	}
	
	void doSearching(){
		int command = -1;
		cout << endl << "***��J�d�ߤ覡***" << endl;
		cout << "0.�h�X\n1.�d�߳浧����\n2.�d�ߪ��~�w�s\n3.�H����d��\n4.�H���ت̬d��\n\n��J�ﶵ:";
		cin >> command;
		while(command != 0){
			switch(command){
				case 0:
					return;
					
				case 1:
					searchByBarcode();
					break;
					
				case 2:{
					string targetItem;
					cout << "--��J�d�ߪ��~:";
					cin >> targetItem;
					searchByItem(targetItem);
					break;
				}
					
				case 3:{
					int searchMonth = 0;
					cin >> searchMonth;
					searchByMonth( searchMonth );
					break;
				}
				case 4:{
					string searchDonor;
					cin >> searchDonor;
					searchByDonor( searchDonor );
					break;
				}
					
				default:
					break;	
				
			}
			cout << endl << "***��J�d�ߤ覡***" << endl;
			cout << "0.�h�X\n1.�d�߳浧����\n2.�d�ߪ��~�w�s\n3.�H����d��\n4.�H���ت̬d��\n\n��J�ﶵ:";
			cin >> command;
		}
	}

	void readFile(){
		string filename = "TotalReceiptList.csv";
		ifstream infile(filename);
		string line;
		std::getline(infile, line); // Ū�����D 
		while( getline(infile, line)){
			stringstream ss(line);
			std::string barcode, month, date, donor, itemName, amount;

	        // �v��Ū�� 
	        std::getline(ss, barcode, ',');
	        std::getline(ss, month, ',');
	        std::getline(ss, date, ',');
	        std::getline(ss, donor, ',');
	        std::getline(ss, itemName, ',');
	        std::getline(ss, amount, ',');
	        
			// �d�ߩγЫج�����SingleReceipt 
			SingleReceipt* receipt = nullptr;
	        for (auto& r : stockList) {
	            if (r.getBarcode() == barcode) {
	                receipt = &r;
	                break;
	            }
	        }
	        if (!receipt) {
	            stockList.emplace_back(barcode);
	            receipt = &stockList.back();
	        }
	
	        // �إ�SingleItem��H�òK�[�i���
	        int intDate = std::stoi(date);
	        int intMonth = std::stoi(month);
	        receipt->addItem(intDate, intMonth, donor, itemName, amount);
	    }
	
	    infile.close();
	    cout << "Ū������: " << fileName << endl;
		
	}

	void save2CSV( string type ) {
		string fileName = "TotalReceiptList";
		fileName = fileName + "." + type;
		ofstream outfile(fileName);
		
		if(!outfile.is_open()){
			cerr << "--���~�}���ɮ�:" << fileName << endl;
			return;
		}

		outfile << "���ڽs��,���,���,���ت�,���~�W��,�ƶq,�����,������,������\n";

		for ( auto & receipt : stockList ){
			//receipt.displayReceipt();
			for( auto & item : receipt.list ){
				outfile << receipt.getBarcode() << ", " << item.getMonth() << "," << item.getDate() << "," << item.getDonor() << "," << item.getItemName() << "," << item.getAmount() << "," << item.recipient << "," << item.outMonth << "," << item.outDate << "," << endl;
			}
		}

		outfile.close();
		cout << "--�w�x�s�A�ɦW: " << fileName;
		
	}
	
	void sortList(){
		sort(stockList.begin(), stockList.end(), [](SingleReceipt &a, SingleReceipt &b) {
			return (a.getBarcode())< b.getBarcode();
		});
	}
	
	void go(){
		readFile();
		sortList();
		cout << "*****�w�s�޲z�t��V1.0*****" << endl; 
		string type = "";
		int command = -1;
		while(command != 0){
			cout << "0.�h�X�{��\n1.���ڿ�J\n2.�w�s���\n3.�L�I�Ҧ��w�s\n4.�j��\n5.��X�ɮ�\n\n--�п�J�ﶵ: ";
			Start:
			cin >> command;
	
			switch(command){
				case 1 :{
					doIncome();
					sortList();
					cout << "--��J�����A�}�l�g��..."<< endl;
					type = "csv";
					save2CSV(type);
					type = "txt";
					save2CSV(type);
					cout << "--�g�ɧ���"<< endl << endl;
					break;
				}
					
				case 2 :
					doTakeOut();
					sortList();
					cout << "--��������A�}�l�g��..." << endl;
					type = "csv";
					save2CSV(type);
					type = "txt";
					save2CSV(type);
					cout << "--�g�ɧ���"<< endl << endl;
					break;
					
				case 3 :
					cout << endl;
					displayStockList();
					break;
					
				case 4 :
					doSearching();
					break;

				case 5:{
				
					type = "csv";
					save2CSV(type);
					type = "txt";
					save2CSV(type);
					cout << "--�g�ɧ���"<< endl << endl;
					break;
				}


				default:{ 
					cout << endl;
					cout << "�ﶵ���~�A�ЦA����J[0~5]:";
					goto Start;	
					break;
				} 
			}
		}

		stockList.clear();
	}
};


int main(){
	StockingSystem stockingSystem;
	stockingSystem.go();
	return 0;
}
