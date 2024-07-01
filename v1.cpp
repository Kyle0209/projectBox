#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

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
   string outMonth;
   string outDate;
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

		outDate = "";
		outMonth = "";
		recipient = "";
	}
	
	SingleItem( int date, int month, string donor, string itemName, string amount ){
		this->date = date;
		this->month = month;
		if( donor == "00" ) this->donor.assign("未紀錄");
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
            cout << "----日期: " << i.getMonth() << "月" << i.getDate() << "日" << "\t捐贈者: " << i.getDonor() << "\t物品名稱: " << i.getItemName() << "\t數量: " << i.getAmount() ;
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
		cout << "----捐贈者(若無輸入\"00\"): " ;
		cin >> donor;
		cout << "----日期(月): ";
		cin >> month ;
		cout << "----日期(日): ";
		cin >> date ;
		cout << "----物品名稱: " ;
		cin >> itemName;
		while( itemName != "N" ){
			cout << "----數量: ";
			cin >> amount ;
			cout << endl;
			
			tempIncome.addItem(date, month, donor, itemName, amount);
			
			cout << "--刪除上一筆請輸入\"D\"\n----物品名稱(若此單結束請輸入\"N\"): " ;
			cin >> itemName;
			while( itemName == "D" || itemName == "d" ){
				if( tempIncome.getListSize() == 0 ){
					cout << "\n--本筆收據為空\n" << endl;
					cout << "----輸入物品名稱(若此單結束請輸入\"N\"): " ;
				}
				
				else{
					tempIncome.popLast();
					cout << endl << "***已刪除前一筆，請重新輸入***"<< endl << endl; 
					cout << "--刪除上一筆請輸入\"D\"\n----物品名稱(若此單結束請輸入\"N\"): " ;
					
				}
				cin >> itemName;
			}
		}	
		
		stockList.push_back(tempIncome);
	}

	void doIncome(){ // 一筆一筆輸入收據 
		string barcode;
		cout << endl << "--請輸入收據編號(若退出輸入請輸入\"N\"): ";
		cin >> barcode;
		while( barcode != "N" ){
			doSingleIncome(barcode);
			
			cout << endl << "--請輸入收據編號(若退出輸入請輸入\"N\"): ";
			cin >> barcode;
		}
		cout << endl;
	}
	
	// 貨物領取 
	void doTakeOut(){ // 出貨邏輯?
		string barcode, itemName;
		string recipient, amount;
		string month, date;

		cout << "--unwritten function.\n" ; 
		displayUntakenList();
		cout << "--請輸入收據編號(若退出輸入請輸入\"N\"): " ;
		cin >> barcode;
		while(barcode != "N"){
			cout << "----領取月份:" ;
			cin >> month;
			cout << "----領取日期:" ;
			cin >> date;
			cout << "----領取物品(退出輸入\"N\"):";
			cin >> itemName;
			while( itemName != "N" && itemName != "n" ){
				cout << "----領取人:";
				cin >> recipient;
				cin.ignore(); // 清除換行符號
				cout << endl;

				for( auto i : stockList ){
					if(i.getBarcode() == barcode){
						i.takingOut(month, date, itemName, recipient);
						break;
					}
				}
				cout << endl;
				cout << "----領取物品(退出輸入\"N\"):";
				cin >> itemName;
			}


			cout << "--請輸入收據編號(若退出輸入請輸入\"N\"): " ;
			cin >> barcode;
		}

		cout << "--領取結束" << endl << endl;
	}
	
	
	//搜索 
	void searchByBarcode(){ // 輸入收據編號，列出所有資訊 
		string barcode;
		int index = 0;
		cout << "--請輸入收據編號(若退出輸入請輸入\"N\"): ";
		cin >> barcode;
		for(const auto &receipt : stockList){
			if( stockList[index].getBarcode() == barcode ){
				stockList[index].displayReceipt();
				break;
			}
		}
		
		
	} 
	
	void searchByItem( string targetItem ){ // 輸入物品名稱，列出所有符合的數據 
		int total = 0;
		for(auto &searchReceipt : stockList){
			for(auto &searchItem : searchReceipt.list){
				if( searchItem.itemName == targetItem ){
					cout << endl; 
					cout << "--" << searchReceipt.getBarcode() << endl;
					cout << "----日期: " << searchItem.getMonth() << "月" << searchItem.getDate() << "日" << "\t捐贈者: " << searchItem.getDonor() << "\t物品名稱: " << searchItem.getItemName() << "\t數量: " << searchItem.getAmount() ;
					if(searchItem.takenOut)
						cout << "\t領取人:" << searchItem.recipient << "\t日期:" << searchItem.outMonth << "\t月" << searchItem.outDate << "日";
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
		cout << endl << "***輸入查詢方式***" << endl;
		cout << "0.退出\n1.查詢單筆收據\n2.查詢物品庫存\n3.以月份查詢\n4.以捐贈者查詢\n\n輸入選項:";
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
					cout << "--輸入查詢物品:";
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
			cout << endl << "***輸入查詢方式***" << endl;
			cout << "0.退出\n1.查詢單筆收據\n2.查詢物品庫存\n3.以月份查詢\n4.以捐贈者查詢\n\n輸入選項:";
			cin >> command;
		}
	}

	void readFile(){
		string filename = "TotalReceiptList.csv";
		ifstream infile(filename);
		string line;
		std::getline(infile, line); // 讀掉標題 
		while( getline(infile, line)){
			stringstream ss(line);
			std::string barcode, month, date, donor, itemName, amount;

	        // 逐欄讀取 
	        std::getline(ss, barcode, ',');
	        std::getline(ss, month, ',');
	        std::getline(ss, date, ',');
	        std::getline(ss, donor, ',');
	        std::getline(ss, itemName, ',');
	        std::getline(ss, amount, ',');
	        
			// 查詢或創建相應的SingleReceipt 
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
	
	        // 建立SingleItem對象並添加進資料
	        int intDate = std::stoi(date);
	        int intMonth = std::stoi(month);
	        receipt->addItem(intDate, intMonth, donor, itemName, amount);
	    }
	
	    infile.close();
	    cout << "讀取完畢: " << fileName << endl;
		
	}

	void save2CSV( string type ) {
		string fileName = "TotalReceiptList";
		fileName = fileName + "." + type;
		ofstream outfile(fileName);
		
		if(!outfile.is_open()){
			cerr << "--錯誤開啟檔案:" << fileName << endl;
			return;
		}

		outfile << "收據編號,月份,日期,捐贈者,物品名稱,數量,領取者,領取月份,領取日期\n";

		for ( auto & receipt : stockList ){
			//receipt.displayReceipt();
			for( auto & item : receipt.list ){
				outfile << receipt.getBarcode() << ", " << item.getMonth() << "," << item.getDate() << "," << item.getDonor() << "," << item.getItemName() << "," << item.getAmount() << "," << item.recipient << "," << item.outMonth << "," << item.outDate << "," << endl;
			}
		}

		outfile.close();
		cout << "--已儲存，檔名: " << fileName;
		
	}
	
	void sortList(){
		sort(stockList.begin(), stockList.end(), [](SingleReceipt &a, SingleReceipt &b) {
			return (a.getBarcode())< b.getBarcode();
		});
	}
	
	void go(){
		readFile();
		sortList();
		cout << "*****庫存管理系統V1.0*****" << endl; 
		string type = "";
		int command = -1;
		while(command != 0){
			cout << "0.退出程序\n1.收據輸入\n2.庫存領取\n3.盤點所有庫存\n4.搜索\n5.輸出檔案\n\n--請輸入選項: ";
			Start:
			cin >> command;
	
			switch(command){
				case 1 :{
					doIncome();
					sortList();
					cout << "--輸入結束，開始寫檔..."<< endl;
					type = "csv";
					save2CSV(type);
					type = "txt";
					save2CSV(type);
					cout << "--寫檔完成"<< endl << endl;
					break;
				}
					
				case 2 :
					doTakeOut();
					sortList();
					cout << "--領取結束，開始寫檔..." << endl;
					type = "csv";
					save2CSV(type);
					type = "txt";
					save2CSV(type);
					cout << "--寫檔完成"<< endl << endl;
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
					cout << "--寫檔完成"<< endl << endl;
					break;
				}


				default:{ 
					cout << endl;
					cout << "選項錯誤，請再次輸入[0~5]:";
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
