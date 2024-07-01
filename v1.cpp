#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;



class SingleItem{
public:
//	進貨區;
	int date;
	int month;
	string donor; // 捐贈者
	string itemName;
	string amount;
	string memo;

// 領取區	 
   int outMonth;
   int outDate;
   string recipient; // 領取人


public:

	bool takenOut;
	
	SingleItem(){
		date = 0;
		month = 0;
		donor = "";
		itemName = "";
		amount = "";
		takenOut = false;
	}
	
	SingleItem( int date, int month, string donor, string itemName, string amount ){
		this->date = date;
		this->month = month;
		if( donor == "00" ) this->donor.assign("未紀錄");
		else this->donor.assign(donor);
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

public:
	vector<SingleItem> list;

public:
	
	SingleReceipt( string barcode ){
		this->barcode.assign(barcode);
	}
	
	void displayReceipt(){
		cout << barcode << endl;
		for (auto& i : list) {
            cout << "日期: " << i.getMonth() << "月" << i.getDate() << "日" << "\t捐贈者: " << i.getDonor() << "\t物品名稱: " << i.getItemName() << "\t數量: " << i.getAmount() ;
			if(i.takenOut)
				cout << "\t領取人:" << i.recipient << "\t日期:" << i.outMonth << "\t月" << i.outDate << "日";
			cout << endl;
        }
		cout << endl;
	}

	void displayUntakenItem(){
		cout << barcode << endl;
		for (auto& i : list) {
			if( !i.takenOut ){
				cout << "日期: " << i.getMonth() << "月" << i.getDate() << "日" << "\t捐贈者: " << i.getDonor() << "\t物品名稱: " << i.getItemName() << "\t數量: " << i.getAmount() << endl;
			}
		}
		cout << endl;
	}

	void takingOut(int month, int date, string itemName, string name){
		for (auto& i : list) {
			if(i.recipient == name){
				i.takenOut = 1;
				i.month = month;
				i.date = date;
				break;
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

	int itemSumming(){ // 回傳本單中某項物品的數量 *********
		return 0;
	};

	

	
	
};

class StockingSystem{
private:
	string fileName; // 寫檔名稱
	vector<SingleReceipt> stockList;  // 總庫存 
	
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
	
	// 物資入倉 
	void doSingleIncome( string barcode ){ // 加入單筆收據內容 
		string donor, itemName;
		int date, month;
		string amount;
		SingleReceipt tempIncome(barcode);
		cout << "捐贈者(若無輸入\"00\"): " ;
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
		string barcode, itemName, name, amount;
		int month, date;

		cout << "unwritten function." ; 
		displayUntakenList();
		cout << "輸入訂單編號:" ;
		cin >> barcode;
		while(barcode != "N"){
			cout << "領取月份:" ;
			cin >> month;
			cout << "領取日期:" ;
			cin >> date;
			cout << "領取物品(退出輸入\"N\"):";
			cin >> itemName;
			while( itemName != "N" && itemName != "n" ){
				cout << "領取人";
				cin >> name;

				for( auto i : stockList ){
					if(i.getBarcode() == barcode){
						i.takingOut(month, date, itemName, name);
						break;
					}
				}
				cout << "領取物品(退出輸入\"N\"):";
				cin >> itemName;
			}


			cout << "輸入訂單編號(退出輸入\"N\"):" ;
			cin >> barcode;
		}

		cout << "領取結束" << endl << endl;
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

	void save2CSV( string type ) {
		string fileName = "TotalReceiptList";
		fileName = fileName + "." + type;
		ofstream outfile(fileName);
		
		if(!outfile.is_open()){
			cerr << "錯誤開啟檔案:" << fileName << endl;
			return;
		}

		outfile << "barcode, month, date, donor, itemname, amount\n";

		for ( auto receipt : stockList ){
			receipt.displayReceipt();
			for( auto item : receipt.list ){
				outfile << receipt.getBarcode() << ", " << item.getMonth() << "月" << item.getDate() << "日," << item.getDonor() << "," << item.getItemName() << "," << item.getAmount() << item.recipient << "," << item.outMonth << "月" << item.outDate << "日" << endl;
			}
		}

		outfile.close();
		cout << "已儲存，檔名: " << fileName;
		
	}
	
	void go(){
		cout << "*****庫存管理系統V1.0*****" << endl; 
		string type = "";
		int command = -1;
		while(command != 0){
			cout << "0.退出程序\n1.收據輸入\n2.庫存領取\n3.盤點所有庫存\n4.搜索\n\n--請輸入選項: ";
			cin >> command;
	
			switch(command){
				case 1 :{
					doIncome();
					cout << "輸入結束，開始寫檔..."<< endl;
					cout << "請輸入想要存檔的類型" << endl;
					cout << "--Excel格式:csv\n--記事本格式:txt\n: ";
					cin >> type;
					save2CSV(type);
					cout << "寫檔完成"<< endl << endl;
					break;
				}
					
				case 2 :
					doTakeOut();
					cout << "領取結束，開始寫黨..." << endl;
					cout << "請輸入想要存檔的類型" << endl;
					cout << "--Excel格式:csv\n--記事本格式:txt\n: ";
					cin >> type;
					save2CSV(type);
					cout << "寫檔完成"<< endl << endl;
					break;
					
				case 3 :
					displayStockList();
					break;
					
				case 4 :
					doSearching();
					break;

				case 5 :{
				 	string i = "";
					cout << "please輸入: " ;
					cin >> i ;
					cout << "輸出: " << i << endl ;
					break; 
				}

				default:
					break;
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
