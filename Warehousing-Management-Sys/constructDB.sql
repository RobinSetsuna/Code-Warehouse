create database market;
use market;
CREATE TABLE Provider (
    P_ID VARCHAR(256),
    P_Name VARCHAR(256),
    P_Address VARCHAR(256),
    P_Phone VARCHAR(20),
    primary key(P_ID)
);

CREATE TABLE Commodity (
    C_ID VARCHAR(256),
    C_Name VARCHAR(256),
    C_Price NUMERIC(10 , 2 ),
    C_Cost NUMERIC(10 , 2 ),
    C_Weight NUMERIC(10 , 2 ),
    C_Category ENUM('Bread', 'Beverage', 'Nuts', 'InstantNoodles'),
    C_Packaging ENUM('Can', 'Bottle', 'Box', 'Bag', 'Cup'),
    C_Capacity int,
    primary key(C_ID)
);

CREATE TABLE Saler (
    S_ID VARCHAR(256),
    S_Name VARCHAR(256),
    S_Salary NUMERIC(20 , 2 ),
    S_Age INT,
    S_Phone VARCHAR(20),
    S_Address VARCHAR(256),
    primary key(S_ID)
	);

CREATE TABLE Warehouse (
    W_ID VARCHAR(256),
    W_Name VARCHAR(256),
    W_Address VARCHAR(256),
    W_Capacity int,
    primary key(W_ID)
);

CREATE TABLE WarehouseStorage(
	C_ID varchar(256),
    W_ID varchar(256),
    Quantity INT,
    WS_ID INT auto_increment,
    primary key(WS_ID),
    foreign key(C_ID)references Commodity(C_ID),
    foreign key(W_ID)references Warehouse(W_ID)
    );
    
CREATE TABLE Monitor (
    M_ID VARCHAR(256),
    M_Name VARCHAR(256),
    M_Phone VARCHAR(256),
    M_Address VARCHAR(256),
    M_Age INT,
    primary key(M_ID)
);
	
CREATE TABLE PurchasingAgent (
    PA_ID VARCHAR(256),
    PA_Name VARCHAR(256),
    PA_Age INT,
    PA_Phone VARCHAR(20),
    PA_Address VARCHAR(256),
    primary key(PA_ID)
);

CREATE TABLE Supervise (
    M_ID VARCHAR(256),
    W_ID VARCHAR(256),
    primary key(M_ID,W_ID),
    foreign key(M_ID)references Monitor(M_ID),
    foreign key(W_ID)references Warehouse(W_ID)
);
	
CREATE TABLE Put (
	Put_ID int auto_increment,
    PA_ID VARCHAR(256),
    P_ID VARCHAR(256),
    C_ID VARCHAR(256),
	W_ID VARCHAR(256),
    PutDate DATE,
    Quantity INT,
    primary key(Put_ID)
);
	
CREATE TABLE OutRecord (
	Out_ID int auto_increment,
    C_ID VARCHAR(256),
    S_ID VARCHAR(256),
    SellDate DATE,
    Quantity INT,
    primary key (Out_ID)
);

create view totalearn as 
	SELECT sum(commodity.C_Price*outrecord.Quantity) as tearn
    FROM outrecord join commodity on commodity.C_ID = outrecord.C_ID;
    
create view totalcost as
	SELECT sum(commodity.C_Cost*put.Quantity) as tcost
	FROM put join commodity on commodity.C_ID = put.C_ID;
	
create view Hottest as
	SELECT commodity.C_Name as CommodityName,MAX(newtable.totalq) as Quantity
    FROM (SELECT outrecord.C_ID as nc_id,sum(outrecord.Quantity) as totalq
			FROM outrecord join commodity on commodity.C_ID = outrecord.C_ID
			GROUP BY commodity.C_ID) as newtable join commodity on commodity.C_ID = newtable.nc_id;
			
create view commodityinfo as 
	select commodity.C_ID, commodity.C_Name, commodity.C_Price, commodity.C_Cost, commodity.C_Weight, commodity.C_Category, commodity.C_Packaging, commodity.C_Capacity, newws.totalquantity
    from (select warehousestorage.C_ID as commodityi, sum(warehousestorage.Quantity) as totalquantity
				from warehousestorage
				group by warehousestorage.C_ID) as newws join commodity on newws.commodityi = commodity.C_ID;

insert into monitor
	values('M001','苏光荣','13768732734','BUPT',21),
    ('M002','顾天飞','17398273527','BUPT',22),
    ('M003', '刘又嘉', '18392831823','PEK',21);
    
insert into saler
	values('S001','顾曲',3000,20,'17387264235','BUPT'),
    ('S002','徐志超',4000,20,'15093829832','BUPT');
    
insert into warehouse
	values('W001','北京仓库','西土城路十号',100),
    ('W002','上海仓库','南京路二十号',100),
    ('W003','国际仓库','Berkely Street',100);
    
insert into supervise
	values('M001','W003'),
    ('M002','W002'),
    ('M003','W001');
    
insert into commodity
    values('C001','可乐',3,1.5,2,'Beverage','Bottle',600),
    ('C002','统一康师傅方便面',4.5,2,2,'InstantNoodles','Box',180),
    ('C003','松果',20,4,5,'Nuts','Bag',30),
    ('C004','法式可颂',10,4,3,'Bread','Bag',20);
    
insert into purchasingagent
	values('PA01','叶梦宇',21,'17862537262','Beijing');



