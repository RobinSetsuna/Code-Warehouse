from django.db import models

# Create your models here.
class Monitor(models.Model):
    M_Id = models.CharField(max_length= 256)
    M_Name = models.CharField(max_length= 256)
    M_Phone = models.CharField(max_length=256)
    M_Address = models.CharField(max_length=256)
    M_Age = models.IntegerField()

    class Meta:
        managed = False
        db_table = 'Monitor'

class Provider(models.Model):
    P_ID = models.CharField(max_length=256)
    P_Name = models.CharField(max_length=256)
    S_Address = models.CharField(max_length=256)
    S_Phone = models.CharField(max_length=20)

    class Meta:
        managed = False
        db_table = 'Provider'

#加入副属性
class Commodity(models.Model):
    CommodityType = (
        ('Nuts','Nuts'),
        ('Bread','Bread'),
        ('Beverage','Beverage'),
        ('InstanNoodles','InstanNoodles'),
    )
    PackType = (
        ('Can', 'Can'),
        ('Bottle', 'Bottle'),
        ('Box', 'Box'),
        ('Bag', 'Bag'),
        ('Cup', 'Cup'),
    )
    C_ID = models.CharField(max_length= 256)
    C_Name = models.CharField(max_length=256)
    C_Cost = models.DecimalField(max_digits= 100,decimal_places=2)
    C_Price = models.DecimalField(max_digits= 20,decimal_places=2)
    C_Weight = models.DecimalField(max_digits= 20,decimal_places=2)
    C_Packaging = models.CharField(max_length= 20,choices=PackType)
    C_Category = models.CharField(max_length= 20,choices=CommodityType)
    C_Capacity = models.IntegerField()
    class Meta:
        managed = False
        db_table = 'Commodity'


class Saler(models.Model):
    S_ID = models.CharField(max_length=256)
    S_Name = models.CharField(max_length=256)
    S_Salary = models.DecimalField(max_digits=20,decimal_places=2)
    S_Age = models.IntegerField()
    S_Phone = models.CharField(max_length=20)
    S_Address = models.CharField(max_length=256)

    class Meta:
        managed = False
        db_table = 'Saler'



class Warehouse(models.Model):
    W_ID = models.CharField(max_length=256)
    W_Name = models.CharField(max_length=256)
    W_Address = models.CharField(max_length=256)
    W_Capacity = models.IntegerField()

    class Meta:
        managed = False
        db_table = 'Warehouse'


class WarehouseStorage(models.Model):
    WS_ID = models.IntegerField(primary_key=True)
    W_ID = models.CharField(max_length=128)
    C_ID = models.CharField(max_length=128)
    Quantity = models.IntegerField()

    class Meta:
        managed = False
        db_table = 'WarehouseStorage'

class PurchasingAgent(models.Model):
    PA_ID = models.CharField(max_length=256)
    PA_Name = models.CharField(max_length=256)
    PA_Age = models.IntegerField()
    PA_Phone = models.CharField(max_length=20)
    PA_Address = models.CharField(max_length=256)


    class Meta:
        managed = False
        db_table = 'PurchasingAgent'

class Supervise(models.Model):
    M_ID = models.CharField(max_length= 256)
    W_ID = models.CharField(max_length= 128, primary_key=True)

    class Meta:
        managed = False
        db_table = 'Supervise'



class Put(models.Model):
    Put_ID = models.IntegerField(primary_key=True)
    PA_ID = models.CharField(max_length= 256)
    P_ID = models.CharField(max_length= 256)
    C_ID = models.CharField(max_length= 256)
    W_ID = models.CharField(max_length= 256)
    PutDate = models.DateField()
    Quantity = models.IntegerField()

    class Meta:
        managed = False
        db_table = 'Put'


class OutRecord(models.Model):
    Out_ID = models.IntegerField(primary_key=True)
    S_ID = models.CharField(max_length=256)
    C_ID = models.CharField(max_length=256)
    SellDate = models.DateField()
    Quantity = models.IntegerField()

    class Meta:
        managed = False
        db_table = 'OutRecord'

class commodityinfo(models.Model):
    CommodityType = (
        ('Nuts','Nuts'),
        ('Bread','Bread'),
        ('Beverage','Beverage'),
        ('InstanNoodles','InstanNoodles'),
    )
    PackType = (
        ('Can', 'Can'),
        ('Bottle', 'Bottle'),
        ('Box', 'Box'),
        ('Bag', 'Bag'),
        ('Cup', 'Cup'),
    )
    C_ID = models.CharField(max_length=128, primary_key=True)
    C_Name = models.CharField(max_length=256)
    C_Cost = models.DecimalField(max_digits= 100,decimal_places=2)
    C_Price = models.DecimalField(max_digits= 20,decimal_places=2)
    C_Weight = models.DecimalField(max_digits= 20,decimal_places=2)
    C_Packaging = models.CharField(max_length= 20,choices=PackType)
    C_Category = models.CharField(max_length= 20,choices=CommodityType)
    C_Capacity = models.IntegerField()
    totalquantity = models.IntegerField()
    class Meta:
        managed = False
        db_table = 'commodityinfo'

class User(models.Model):
    username = models.CharField(max_length=50)
    password = models.CharField(max_length=50)

    def __unicode__(self):
        return  self.username