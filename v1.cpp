#include <iostream>
#include <vector>

using namespace std;

/*筆記:
	功能一完成
*/ 

class SingleItem{
private:
//	string barcode;
	int date;
	int month;
	string donor;
	string itemName;
	string amount;
	string memo;
	bool takenOut; 
	// int

public:
	SingleItem(){
		date = 0;
		month = 0;
		donor = "";
		itemName = "";
		amount = "";
	}
	
	SingleItem( int date, int month, string donor, string itemName, string amount ){
		this->date = date;
		this->month = month;
		this->donor.assign(donor);
		this->itemName.assign(itemName);
		this->amount.assign(amount);
	}
	
	void setDate(const int& date) {
        this->date = date;
    }

	void setMonth( const int& month){
		this->month = month;
	}

    void setDonor(const string& donor) {
        this->donor = donor;
    }

    void setItemName(const string& itemName) {
        this->itemName = itemName;
    }

    void setAmount(string amount) {
        this->amount.assign(amount);
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
	vector<SingleItem> list;

public:
	
	SingleReceipt( string barcode ){
		this->barcode.assign(barcode);
	}
	
	void displayReceipt(){
		cout << barcode << endl;
		for (auto& i : list) {
            cout << "日期: " << i.getMonth() << "月" << i.getDate() << "日" << "\t捐贈者: " << i.getDonor() << "\t物品名稱: " << i.getItemName() << "\t數量: " << i.getAmount() << endl;
        }
		cout << endl;
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

	int itemSumming(){ // 回傳本單中某項物品的數量 
		return 0;
	};
	
	
};

class StockingSystem{
private:
	
	vector<SingleReceipt> stockList;  // 總庫存 
	
public:
	
	void displayStockList(){
		for(auto i : stockList){
			i.displayReceipt();
		}
	}
	
	// 物資入倉 
	void doSingleIncome( string barcode ){ // 加入單筆收據內容 
		string donor, itemName;
		int date, month;
		string amount;
		SingleReceipt tempIncome(barcode);
		cout << "捐贈者: " ;
		cin >> donor;
		cout << "日期(月): ";
		cin >> month ;
		cout << "日期(日): ";
		cin >> date ;
		cout << "物品名稱: " ;
		cin >> itemName;
		while( itemName != "N" ){
			cout << "數量: ";
			cin >> amount ;
			cout << endl;
			
			tempIncome.addItem(date, month, donor, itemName, amount);
			
			cout << "刪除上一筆請輸入\"D\"\n物品名稱(若此單結束請輸入\"N\"): " ;
			cin >> itemName;
			while( itemName == "D" ){
				if( tempIncome.getListSize() == 0 ){
					cout << "\n本筆收據為空\n" << endl;
					cout << "輸入物品名稱(若此單結束請輸入\"N\"): " ;
				}
				
				else{
					tempIncome.popLast();
					cout << endl << "***已刪除前一筆，請重新輸入***"<< endl << endl; 
					cout << "刪除上一筆請輸入\"D\"\n物品名稱(若此單結束請輸入\"N\"): " ;
					
				}
				cin >> itemName;
			}
		}	
		
		stockList.push_back(tempIncome);
	}

	void doIncome(){ // 一筆一筆輸入收據 
		string barcode;
		cout << endl << "請輸入收據編號(若退出輸入請輸入\"N\"): "" ";
		cin >> barcode;
		while( barcode != "N" ){
			doSingleIncome(barcode);
			
			cout << endl << "請輸入收據編號(若退出輸入請輸入\"N\"): ";
			cin >> barcode;
		}
		cout << endl;
	}
	
	// 貨物領取 
	void doTakeOut(){ // 出貨邏輯? 
		cout << "unwritten function." ; 
		
	}
	
	
	//搜索 
	void searchByBarcode(){ // 輸入收據編號，列出所有資訊 
		string barcode;
		int index = 0;
		cout << "輸入收據編號:";
		cin >> barcode;
		for( ; index < stockList.size() ; index++ ){
			if( stockList[index].getBarcode() == barcode ){
				stockList[index].displayReceipt();
				break;
			}
		}
		
		
	} 
	
	void searchByItem(){ // 輸入物品名稱，列出所有符合的數據 
		
	}
	
	void doSearching(){
		int command = -1;
		cout << endl << "***輸入查詢方式***" << endl;
		cout << "0.退出\n1.查詢單筆收據\n2.查詢物品庫存\n\n輸入選項:";
		cin >> command;
		while(command != 0){
			switch(command){
				case 0:
					return;
					
				case 1:
					searchByBarcode();
					break;
					
				case 2:
					searchByItem();
					break;
					
				case 3:
					//searchByDate();
					
				case 4:
					//searchByDonor();
					
				default:
					break;	
				
			}
			cout << endl << "***輸入查詢方式***" << endl;
			cout << "0.退出\n1.查詢單筆收據\n2.查詢物品庫存\n\n輸入選項:";
			cin >> command;
		}
	}
	
	void go(){
		cout << "*****庫存管理系統V1.0*****" << endl; 
		
		int command;
		cout << "0.退出程序\n1.收據輸入\n2.庫存領取\n3.盤點所有庫存\n4.搜索\n\n--請輸入選項: ";
		
		cin >> command;
		while(command != 0){
	
			switch(command){
				case 1 :
					doIncome();
					break;
					
				case 2 :
					doTakeOut();
					break;
					
				case 3 :
					displayStockList();
					break;
					
				case 4 :
					doSearching();
					break;
					
				default:
					break;
			}
			cout << "0.退出程序\n1.收據輸入\n2.庫存領取\n3.盤點所有庫存\n\n--請輸入選項: ";
			cin >> command;
		}
	}
};


int main(){
	StockingSystem stockingSystem;
	stockingSystem.go();
	return 0;
}
