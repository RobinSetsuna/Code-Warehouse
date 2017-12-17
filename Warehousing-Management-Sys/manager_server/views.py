from django.shortcuts import render, HttpResponse, HttpResponseRedirect
from django.http import JsonResponse
from django.contrib.auth.decorators import login_required
from django.contrib.auth.models import User
from django.contrib import auth
import  datetime
from django.db import transaction
from django.forms.models import model_to_dict

from .models import Monitor, Commodity, Provider, PurchasingAgent, Warehouse, Saler, Put, OutRecord, hottest, totalcost, totalearn, Supervise, commodityinfo

# Create your views here.

def register_view(request):
    if request.method == "POST":
        userName = request.POST['username']
        passWord1 = request.POST['password1']
        passWord2 = request.POST['password2']
        if len(User.objects.filter(username=userName)) > 0 :
            return HttpResponse("The user name has benn used before, please change another one!")
        elif passWord1 != passWord2:
            return HttpResponse("Please input the same passwords.")
        else:
            user = User.objects.create_user(userName, None, passWord1)
            # group = Group.objects.filter(name="manager")
            # if len(group) == 0:
            #     group = Group.objects.create(name="manager")
            #     group.permissions.add()
            # user.groups.add(group)
            return HttpResponseRedirect("/manager/login/")
    else:
        return render(request, "manager_temp/log_temp/register.html")

def login_view(request):
    if request.method == "POST":
        userName = request.POST['username']
        passWord = request.POST['password']
        user = auth.authenticate(username = userName, password = passWord)
        if user is not None:
            auth.login(request, user)
            return HttpResponseRedirect("/manager/statistics/")
        else:
            return HttpResponse("failed in logining")
    elif request.method == "GET":
        return render(request, "manager_temp/log_temp/login.html")

@login_required
def logout_view(request):
    auth.logout(request)
    return HttpResponseRedirect('/manager/login/')

@login_required
def query(request):
    if request.method == "POST":
        return render(request, "manager_temp/query.html")
    elif request.method == "GET":
        commodityList = Commodity.objects.all()
        return render(request, "manager_temp/query.html", {"commodityList": commodityList, "managerName": request.user.username})

@login_required
def statistics(request):
    print(123)
    # if request.method == "POST":
    #     return render(request, "manager_temp/statistics.html")
    if request.method == "GET":
        cNum = len(Commodity.objects.all())
        wNum = len(Warehouse.objects.all())
        sNum = len(Saler.objects.all())
        paNum = len(PurchasingAgent.objects.all())
        mNum = len(Monitor.objects.all())
        pNum = len(Put.objects.all())
        oNum = len(OutRecord.objects.all())
        Name = hottest.objects.all()[0].CommodityName
        TotalEarn = totalearn.objects.all()[0].tearn
        TotalCost = totalcost.objects.all()[0].tcost
        totalNum = {"commodityNum": cNum, "warehouseNum": wNum, "purchasingAgentNum": paNum,
                    "salerNum": sNum, "monitorNum": mNum, "putNum": pNum, "outNum": oNum, "Name": Name,
                    "TotalEarn": TotalEarn, "TotalCost": TotalCost}
        return render(request, "manager_temp/statistics.html", {"totalNum": totalNum,
                                                                "managerName": request.user.username})

@login_required
def storage(request):
    # if request.method == "POST":
    #     return render(request, "manager_temp/storage.html")
    if request.method == "GET":
        return render(request, "manager_temp/storage.html", {"managerName": request.user.username})

#for test
@login_required
def query_commodity(request):
    if request.method == "POST":
        cId = request.POST["commodityId"]
        cName = request.POST["commodityName"]
        cPrice = request.POST["commodityPrice"]
        # print(cId + ',' + cName + ',' + cPrice)
        commodityList = Commodity.objects.all()
        tempCommodityList = []
        for tuples in commodityList:
            if ((cId == "" or cId in tuples.C_ID)
                and (cName == "" or cName in tuples.C_Name)
                and (cPrice == "" or tuples.C_Price == int(cPrice))):
                tempCommodityList.append({"C_ID": tuples.C_ID, "C_Name": tuples.C_Name, "C_Cost": tuples.C_Cost,
                                            "C_Price": tuples.C_Price, "C_Weight": tuples.C_Weight, "C_Packaging": tuples.C_Packaging,
                                          "C_Category": tuples.C_Category,"C_Capacity": tuples.C_Capacity})
        print(tempCommodityList)
        return JsonResponse({"commodityList": tempCommodityList})
    else:
        return JsonResponse({"result": "error"})

@login_required
def query_monitor(request):
    if request.method == "POST":
        mId = request.POST["monitorId"]
        mName = request.POST["monitorName"]
        mAge = request.POST["monitorAge"]

        tempMonitorList = []
        monitorList = Monitor.objects.all()
        for tuples in monitorList:
            if ((mId == "" or mId in tuples.M_ID)
                and (mName == "" or mName in tuples.M_Name)
                and (mAge == "" or tuples.M_Age == int(mAge))):
                tempMonitorList.append({"M_ID": tuples.M_ID, "M_Name": tuples.M_Name, "M_Phone": tuples.M_Phone,
                                        "M_Address": tuples.M_Address, "M_Age": tuples.M_Age})
        return JsonResponse({"monitorList": tempMonitorList})

    else:
        return JsonResponse({"result": "error"})

@login_required
def query_warehouse(request):
    if request.method == "POST":
        wId = request.POST["warehouseId"]
        wName = request.POST["warehouseName"]

        tempWarehouseList = []
        warehouseList = Warehouse.objects.all()
        # print("1")
        for tuples in warehouseList:
            if ((wId == "" or wId in tuples.W_ID)
                and (wName == "" or wName in tuples.W_Name)):
                # print("2")
                # print(tuples.W_ID)
                supervise = Supervise.objects.get(W_ID=tuples.W_ID)
                # print(supervise.M_ID)
                M_ID = supervise.M_ID#对应监管人ID
                tempWarehouseList.append({"W_ID": tuples.W_ID, "W_Name": tuples.W_Name, "W_Monitor": M_ID,
                                          "W_Address": tuples.W_Address, "W_Capacity": tuples.W_Capacity})

        return JsonResponse({"warehouseList": tempWarehouseList})

    else:
        return JsonResponse({"result": "error"})

@login_required
def query_putlog(request):
    if request.method == "POST":
        pMonth = request.POST["putLogMonth"]
        if pMonth != "":
            queryMonth = datetime.datetime.strptime(pMonth, '%Y-%m')
            # print(queryMonth)
            tempPutLogList = []
            putLogList = Put.objects.all()
            for tuples in putLogList:
                if (queryMonth.year == tuples.PutDate.year and
                queryMonth.month == tuples.PutDate.month):
                    # print(tuples.SellDate)
                    tempPutLogList.append({"PA_ID": tuples.PA_ID, "P_ID": tuples.P_ID,
                                           "C_ID": tuples.C_ID, "PutDate": tuples.PutDate,
                                           "Quantity": tuples.Quantity, "Put_ID": tuples.Put_ID})
            # print(tempPutLogList)
            return JsonResponse({"putLogList": tempPutLogList})
        else:
            tempPutLogList = []
            putLogList = Put.objects.all()
            for tuples in putLogList:
                tempPutLogList.append({"PA_ID": tuples.PA_ID, "P_ID": tuples.P_ID,
                                       "C_ID": tuples.C_ID, "PutDate": tuples.PutDate,
                                       "Quantity": tuples.Quantity, "Put_ID": tuples.Put_ID})
            # print(tempPutLogList)
            return JsonResponse({"putLogList": tempPutLogList})
    return JsonResponse({"result": "error"})

@login_required
def query_outlog(request):
    if request.method == "POST":
        oMonth = request.POST["outLogMonth"]
        if oMonth != "":
            queryMonth = datetime.datetime.strptime(oMonth, '%Y-%m')
            print(queryMonth)
            tempOutLogList = []
            outLogList = OutRecord.objects.all()
            for tuples in outLogList:
                if (queryMonth.year == tuples.SellDate.year and
                queryMonth.month == tuples.SellDate.month):
                    print(tuples.SellDate)
                    tempOutLogList.append({"S_ID": tuples.S_ID, "C_ID": tuples.C_ID,
                                           "SellDate": tuples.SellDate, "Quantity": tuples.Quantity,
                                           "Out_ID": tuples.Out_ID})
            print(tempOutLogList)
            return JsonResponse({"outLogList": tempOutLogList})
        else:
            tempOutLogList = []
            outLogList = OutRecord.objects.all()
            for tuples in outLogList:
                tempOutLogList.append({"S_ID": tuples.S_ID, "C_ID": tuples.C_ID,
                                       "SellDate": tuples.SellDate, "Quantity": tuples.Quantity,
                                       "Out_ID": tuples.Out_ID})
            print(tempOutLogList)
            return JsonResponse({"outLogList": tempOutLogList})
    return JsonResponse({"result": "error"})

#add
@transaction.atomic()
@login_required
def add_monitor(request):
    print("addMonitor")
    if request.method == "POST":
        Monitor.objects.create(M_ID=request.POST["M_ID"],
                          M_Name=request.POST["M_Name"],
                          M_Phone=request.POST["M_Phone"],
                          M_Address=request.POST["M_Address"],
                          M_Age=request.POST["M_Age"])
        result = "Success!"
        print(result)
        return JsonResponse({"result": result})

@transaction.atomic()
@login_required
def add_commodity(request):
    print("addCommodity")
    if request.method == "POST":
        Commodity.objects.create(C_ID=request.POST["C_ID"],
                          C_Name=request.POST["C_Name"],
                          C_Price=request.POST["C_Price"],
                          C_Cost=request.POST["C_Cost"],
                          C_Weight=request.POST["C_Weight"],
                          C_Category=request.POST["C_Category"],
                          C_Packaging=request.POST["C_Packaging"],
                          C_Capacity=request.POST["C_Capacity"])
    result = "Success!"
    print(result)
    return JsonResponse({"result": result})

@transaction.atomic()
@login_required
def add_provider(request):
    print("addProvider")
    if request.method == "POST":
        Provider.objects.create(P_ID=request.POST["P_ID"],
                            P_Name=request.POST["P_Name"],
                            P_Address=request.POST["P_Address"],
                            P_Phone=request.POST["P_Phone"])
        result = "Success!"
        print(result)
        return JsonResponse({"result": result})

@transaction.atomic()
@login_required
def add_purchasingAgent(request):
    print("addPurchasingAgent")
    if request.method == "POST":
        PurchasingAgent.objects.create(PA_ID=request.POST["PA_ID"],
                                          PA_Name=request.POST["PA_Name"],
                                          PA_Age=request.POST["PA_Age"],
                                          PA_Address=request.POST["PA_Address"],
                                          PA_Phone=request.POST["PA_Phone"])
        result = "Success!"
        print(result)
        return JsonResponse({"result": result})

@transaction.atomic()
@login_required
def add_warehouse(request):
    print("addwarehouse")
    if request.method == "POST":
        M_ID = request.POST["W_Monitor"]
        if len(Monitor.objects.filter(M_ID=M_ID)) == 0:
            result = "Failed in adding warehouse. Please input the valid Monitor ID."
        else:
            Warehouse.objects.create(W_ID=request.POST["W_ID"],
                                  W_Name=request.POST["W_Name"],
                                  W_Capacity=int(request.POST["W_Capacity"]),
                                  W_Address=request.POST["W_Address"], )

            Supervise.objects.create(M_ID = M_ID, W_ID=request.POST["W_ID"])
            result = "Success!"
        print(result)
        return JsonResponse({"result": result})

@transaction.atomic()
@login_required
def add_saler(request):
    print("addsaler")
    if request.method == "POST":
        Saler.objects.create(S_ID=request.POST["S_ID"],
                      S_Name=request.POST["S_Name"],
                      S_Age=request.POST["S_Age"],
                      S_Phone=request.POST["S_Phone"],
                      S_Address=request.POST["S_Address"],
                      S_Salary=request.POST["S_Salary"], )

        result = "Success!"
        print(result)
        return JsonResponse({"result": result})

#delete
@transaction.atomic()
@login_required
def delete_commodity(request):
    if request.method == "POST":
        print("delete_commodity")
        deleteId = request.POST["deleteCommodityId"]
        commodity = Commodity.objects.filter(C_ID=deleteId)
        if len(commodity) != 0:
            commodity.delete()
        commodityList = Commodity.objects.all()
        tempCommodityList = []
        for tuples in commodityList:
            tempCommodityList.append({"C_ID": tuples.C_ID, "C_Name": tuples.C_Name, "C_Cost": tuples.C_Cost,
                                      "C_Price": tuples.C_Price, "C_Weight": tuples.C_Weight,
                                      "C_Packaging": tuples.C_Packaging,
                                      "C_Category": tuples.C_Packaging, "C_Capacity": tuples.C_Capacity})
        print(tempCommodityList)
        return JsonResponse({"commodityList":tempCommodityList})
    else:
        return HttpResponse("Error!")

@transaction.atomic()
@login_required
def delete_monitor(request):
    if request.method == "POST":
        print("delete_monitor")
        deleteId = request.POST["deleteMonitorId"]
        monitor = Monitor.objects.filter(M_ID=deleteId)
        if len(monitor) != 0:
            monitor.delete()
        monitorList = Monitor.objects.all()
        tempMonitorList = []
        for tuples in monitorList:
            tempMonitorList.append({"M_ID": tuples.M_ID, "M_Name": tuples.M_Name, "M_Phone": tuples.M_Phone,
                                    "M_Address": tuples.M_Address, "M_Age": tuples.M_Age})
        print(tempMonitorList)
        return JsonResponse({"monitorList":tempMonitorList})
    else:
        return HttpResponse("Error!")

@transaction.atomic()
@login_required
def delete_warehouse(request):
    if request.method == "POST":
        print("delete_warehouse")
        deleteId = request.POST["deleteWarehouseId"]
        warehouse = Warehouse.objects.filter(W_ID=deleteId)
        supervise = Supervise.objects.get(W_ID=deleteId)
        if len(warehouse) != 0:
            supervise.delete()
            warehouse.delete()
        warehouseList = Warehouse.objects.all()
        tempWarehouseList = []
        for tuples in warehouseList:
            supervise = Supervise.objects.get(W_ID=tuples.W_ID)
            M_ID = supervise.M_ID  # 对应监管人ID
            tempWarehouseList.append({"W_ID": tuples.W_ID, "W_Name": tuples.W_Name, "W_Monitor": M_ID,
                                      "W_Address": tuples.W_Address, "W_Capacity": tuples.W_Capacity})
        print(tempWarehouseList)
        return JsonResponse({"warehouseList":tempWarehouseList})
    else:
        return HttpResponse("Error!")

@transaction.atomic()
@login_required
def delete_putLog(request):
    if request.method == "POST":
        print("delete_putLog")
        deleteId = request.POST["deletePutLogId"]
        putLog = Put.objects.filter(Put_ID=deleteId)
        if len(putLog) != 0:
            putLog.delete()
        putLogList = Put.objects.all()
        tempPutLogList = []
        for tuples in putLogList:
            tempPutLogList.append({"PA_ID": tuples.PA_ID, "P_ID": tuples.P_ID,
                                   "C_ID": tuples.C_ID, "PutDate": tuples.PutDate,
                                   "Quantity": tuples.Quantity, "Put_ID": tuples.Put_ID})
        print(tempPutLogList)
        return JsonResponse({"putLogList":tempPutLogList})
    else:
        return HttpResponse("Error!")

@transaction.atomic()
@login_required
def delete_outLog(request):
    if request.method == "POST":
        print("delete_outLog")
        deleteId = request.POST["deleteOutLogId"]
        outLog = OutRecord.objects.filter(Out_ID=deleteId)
        if len(outLog) != 0:
            outLog.delete()
        outLogList = OutRecord.objects.all()
        tempOutLogList = []
        for tuples in outLogList:
            tempOutLogList.append({"S_ID": tuples.S_ID, "C_ID": tuples.C_ID,
                                   "SellDate": tuples.SellDate, "Quantity": tuples.Quantity,
                                   "Out_ID": tuples.Out_ID})
        print(tempOutLogList)
        return JsonResponse({"outLogList":tempOutLogList})
    else:
        return HttpResponse("Error!")

#edify
@transaction.atomic()
@login_required
def edify_commodity(request):
    if request.method == "POST":
        commodity = Commodity.objects.get(C_ID=request.POST["edifyCommodityId"])
        if commodity == None:
            return HttpResponse("error!")
        commodity.C_Name = request.POST["edifyCommodityName"]
        commodity.C_Price = request.POST["edifyCommodityPrice"]
        commodity.save()
    #transfer into dict
    commodityList = Commodity.objects.all()
    tempCommodityList = []
    for tuples in commodityList:
        tempCommodityList.append({"C_ID": tuples.C_ID, "C_Name": tuples.C_Name, "C_Cost": tuples.C_Cost,
                                  "C_Price": tuples.C_Price, "C_Weight": tuples.C_Weight,
                                  "C_Packaging": tuples.C_Packaging,
                                  "C_Category": tuples.C_Packaging, "C_Capacity": tuples.C_Capacity})
    return JsonResponse({"commodityList": tempCommodityList})

@transaction.atomic()
@login_required
def edify_monitor(request):
    if request.method == "POST":
        monitor = Monitor.objects.get(M_ID=request.POST["edifyMonitorId"])
        if monitor == None:
            return HttpResponse("error!")
        monitor.M_Name = request.POST["edifyMonitorName"]
        monitor.M_Phone = request.POST["edifyMonitorPhone"]
        monitor.M_Address = request.POST["edifyMonitorAddress"]
        monitor.M_Age = request.POST["edifyMonitorAge"]
        monitor.save()
    #transfer into dict
    monitorList = Monitor.objects.all()
    tempMonitorList = []
    for tuples in monitorList:
        tempMonitorList.append({"M_ID": tuples.M_ID, "M_Name": tuples.M_Name, "M_Phone": tuples.M_Phone,
                                  "M_Address": tuples.M_Address, "M_Age": tuples.M_Age})
    return JsonResponse({"monitorList": tempMonitorList})

@transaction.atomic()
@login_required
def edify_warehouse(request):
    if request.method == "POST":
        warehouse = Warehouse.objects.get(W_ID=request.POST["edifyWarehouseId"])
        if warehouse == None:
            return HttpResponse("error!")
        warehouse.W_Name = request.POST["edifyWarehouseName"]
        warehouse.W_Address = request.POST["edifyWarehouseAddress"]
        warehouse.W_Capacity = request.POST["edifyWarehouseCapacity"]
        warehouse.save()
    #transfer into dict
    warehouseList = Warehouse.objects.all()
    tempWarehouseList = []
    for tuples in warehouseList:
        supervise = Supervise.objects.get(W_ID=tuples.W_ID)
        M_ID = supervise.M_ID
        tempWarehouseList.append({"W_ID": tuples.W_ID, "W_Name": tuples.W_Name, "W_Monitor": M_ID,
                                  "W_Address": tuples.W_Address, "W_Capacity": tuples.W_Capacity})
    return JsonResponse({"warehouseList": tempWarehouseList})
#添加编辑功能