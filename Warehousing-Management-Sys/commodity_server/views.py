from django.shortcuts import render, HttpResponse, HttpResponseRedirect
from django.http import JsonResponse
from django.contrib.auth.decorators import login_required
from django.contrib.auth.models import User
from django.contrib import auth
from . import models
from django.db import transaction
import time
# Create your views here.


def register_view(request):
    if request.method == "POST":
        userName = request.POST['username']
        passWord = request.POST['password']
        User.objects.create_user(userName, None, passWord)
        return HttpResponseRedirect("/saler/login/")
    else:
        return render(request, "saler_temp/log_temp/register.html")

def login_view(request):
    if request.method == "POST":
        userName = request.POST['username']
        passWord = request.POST['password']
        user = auth.authenticate(username = userName, password = passWord)
        if user is not None:
            auth.login(request, user)
            return HttpResponseRedirect("/saler/index/")
        else:
            return HttpResponse("failed in logining")
    elif request.method == "GET":
        return render(request, "saler_temp/log_temp/login.html")

@login_required
def logout_view(request):
    auth.logout(request)
    return HttpResponseRedirect('/saler/login/')

@login_required
def index(request):
    if request.method == "GET":
        userName = request.user.username

        putLogList = models.Put.objects.all()
        tempPutLogList = []
        for tuples in putLogList:
            tempPutLogList.append({"PA_ID": tuples.PA_ID, "P_ID": tuples.P_ID,
                                   "C_ID": tuples.C_ID, "PutDate": tuples.PutDate,
                                   "Quantity": tuples.Quantity, "Put_ID": tuples.Put_ID})

        outLogList = models.OutRecord.objects.all()
        tempOutLogList = []
        for tuples in outLogList:
            tempOutLogList.append({"S_ID": tuples.S_ID, "C_ID": tuples.C_ID,
                                   "SellDate": tuples.SellDate, "Quantity": tuples.Quantity,
                                   "Out_ID": tuples.Out_ID})

        return render(request, "saler_temp/index.html", {"outLogList": tempOutLogList,
                                                         "putLogList": tempPutLogList,
                                                         "username": userName})
    else:
        return HttpResponse("error!")


@transaction.atomic()
@login_required
def warehousing(request):
    if request.method == "GET":
        userName = request.user.username
        return render(request, "saler_temp/warehousing.html", {"username": userName})
    elif request.method == "POST":
        commodityId = request.POST["commodityId"]
        purchasingAgentId = request.POST["purchasingAgentId"]
        providerId = request.POST["providerId"]
        quantity = request.POST["quantity"]
        warehouse = request.POST["warehouse"]
        date = time.strftime("%Y-%m-%d")
        # print(commodityId + "," + purchasingAgentId + "," + providerId + "," + quantity)
    #   入库生成记录请添加
        models.Put.objects.create(PA_ID=purchasingAgentId, P_ID=providerId, C_ID=commodityId, Quantity=quantity, PutDate=date)
        flag = models.WarehouseStorage.objects.filter(W_ID=warehouse, C_ID=commodityId)
        if flag:
            oldquantity = models.WarehouseStorage.objects.get(W_ID=warehouse, C_ID=commodityId).Quantity
            models.WarehouseStorage.objects.filter(W_ID=warehouse, C_ID=commodityId).update(Quantity=oldquantity+int(quantity))
        else:
            models.WarehouseStorage.objects.create(W_ID=warehouse,C_ID=commodityId,Quantity=quantity)
            print("ok")
        result = "success in warehousing"
        return JsonResponse({"result": result})

@transaction.atomic()
@login_required
def selling(request):
    if request.method == "GET":
        userName = request.user.username
        commodityList = models.commodityinfo.objects.all()
        tempCommodityList = []
        for tuples in commodityList:
            tempCommodityList.append({"C_ID": tuples.C_ID, "C_Name": tuples.C_Name, "C_Cost": tuples.C_Cost,
                                          "totalQuantity": tuples.totalquantity,
                                          "C_Price": tuples.C_Price, "C_Weight": tuples.C_Weight,
                                          "C_Packaging": tuples.C_Packaging,
                                          "C_Category": tuples.C_Category, "C_Capacity": tuples.C_Capacity})
        return render(request, "saler_temp/selling.html", {"username": userName,"commodityList":tempCommodityList})
    elif request.method == "POST":
        commodityId = request.POST["commodityId"]
        salerId = request.POST["salerId"]
        quantity = int(request.POST["quantity"])
        date = time.strftime("%Y-%m-%d")
        # print(commodityId + ',' + salerId + ',' + quantity)
        #添加一个账单表,同时条件判断result的返回值
        commodity = models.commodityinfo.objects.get(C_ID=commodityId)
        #判断总量
        if quantity > commodity.totalquantity :
            return JsonResponse({"result": "out of the total saverage!"})

        models.OutRecord.objects.create(S_ID=salerId, C_ID=commodityId, SellDate=date, Quantity=quantity)
        #循环比较
        warehouseStorage = models.WarehouseStorage.objects.all()
        for tuples in warehouseStorage:
            if quantity == 0:
                break
            if tuples.C_ID == commodityId:
                if tuples.Quantity <= quantity:
                    quantity -= tuples.Quantity
                    tuples.delete()
                else:
                    tuples.Quantity -= quantity
                    quantity = 0
                    tuples.save()
                    break

        commodityList = models.commodityinfo.objects.all()
        tempCommodityList = []
        for tuples in commodityList:
             tempCommodityList.append({"C_ID": tuples.C_ID, "C_Name": tuples.C_Name, "C_Cost": tuples.C_Cost,
                                            "totalQuantity": tuples.totalquantity,
                                            "C_Price": tuples.C_Price, "C_Weight": tuples.C_Weight,
                                            "C_Packaging": tuples.C_Packaging,
                                            "C_Category": tuples.C_Category, "C_Capacity": tuples.C_Capacity})
        return JsonResponse({"commodityList": tempCommodityList, "result": "succeed in selling"})
    else:
        return JsonResponse({"result": "error"})

@transaction.atomic()
@login_required
def withdraw_putLog(request):
    if request.method == "POST":
        wPutId = request.POST["Put_ID"]
        putLog = models.Put.objects.filter(Put_ID=wPutId)
        checkid = models.Put.objects.get(Put_ID=wPutId).C_ID
        quantitytodelete = models.Put.objects.get(Put_ID=wPutId).Quantity
        if len(putLog) != 0:
            quantity = models.WarehouseStorage.objects.filter(C_ID=checkid)[0].Quantity
            models.WarehouseStorage.objects.filter(C_ID=checkid).update(Quantity=quantity-quantitytodelete)
            if models.WarehouseStorage.objects.filter(C_ID=checkid)[0].Quantity <= 0:
                models.WarehouseStorage.objects.filter(C_ID=checkid).delete()
            putLog.delete()
        putLogList = models.Put.objects.all()
        tempPutLogList = []
        for tuples in putLogList:
            tempPutLogList.append({"PA_ID": tuples.PA_ID, "P_ID": tuples.P_ID,
                                   "C_ID": tuples.C_ID, "PutDate": tuples.PutDate,
                                   "Quantity": tuples.Quantity, "Put_ID": tuples.Put_ID})
        return JsonResponse({"putLogList": tempPutLogList})

    return HttpResponse("error!")

@transaction.atomic()
@login_required
def withdraw_outLog(request):
    if request.method == "POST":
        wOutId = request.POST["Out_ID"]
        outLog = models.OutRecord.objects.filter(Out_ID=wOutId)
        checkid = models.OutRecord.objects.get(Out_ID=wOutId).C_ID
        quantityToRecover = models.OutRecord.objects.get(Out_ID=wOutId).Quantity
        print("01")
        if len(outLog) != 0:
            print("02")
            tempWSList = models.WarehouseStorage.objects.filter(C_ID=checkid)
            print(checkid)
            if len(tempWSList) == 0:
                models.WarehouseStorage.objects.create(C_ID=checkid,W_ID='W001',Quantity=quantityToRecover)
            else:
                print(models.WarehouseStorage.objects.filter(C_ID=checkid))
                quantity = models.WarehouseStorage.objects.filter(C_ID=checkid)[0].Quantity
                models.WarehouseStorage.objects.filter(C_ID=checkid).update(Quantity=quantity + quantityToRecover)
            outLog.delete()
        outLogList = models.OutRecord.objects.all()
        tempOutLogList = []
        for tuples in outLogList:
            tempOutLogList.append({"S_ID": tuples.S_ID, "C_ID": tuples.C_ID,
                                   "SellDate": tuples.SellDate, "Quantity": tuples.Quantity,
                                   "Out_ID": tuples.Out_ID})
        return JsonResponse({"outLogList": tempOutLogList})

    return HttpResponse("error!")


@login_required
@transaction.atomic
def transfer(request):
    if request.method == "GET":
        userName = request.user.username
        return render(request, "saler_temp/transfer.html", {"username": userName})
    elif request.method == "POST":
        commodityId = request.POST["commodityId"]
        print(commodityId)
        warehouseId = request.POST["warehouseId"]
        quantity = request.POST["quantity"]
        transferedwarehouseId = request.POST["transferedwarehouseId"]
        former = models.WarehouseStorage.objects.filter(C_ID=commodityId, W_ID=transferedwarehouseId)
        print("alreadyfilt")
        if len(former) != 0:
            print("in")
            models.WarehouseStorage.objects.filter(C_ID=commodityId).update(
                Quantity=models.WarehouseStorage.objects.get(C_ID=commodityId,
                                                             W_ID=transferedwarehouseId).Quantity - int(quantity))
            print ("alreadyupdate01")
            latter = models.WarehouseStorage.objects.filter(C_ID=commodityId, W_ID=warehouseId)
            if latter:
                models.WarehouseStorage.objects.filter(W_ID=warehouseId).update(
                    Quantity=models.WarehouseStorage.objects.get(C_ID=commodityId, W_ID=warehouseId).Quantity + int(
                        quantity))
            else:
                models.WarehouseStorage.objects.create(C_ID=commodityId, W_ID=warehouseId, Quantity=quantity)
            result = "success in transferring"
            return JsonResponse({"result": result})
        else:
            result = "failed in transferring"
            return JsonResponse({"result": result})
