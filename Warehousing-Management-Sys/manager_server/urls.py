from django.conf.urls import url
from . import views

urlpatterns = [
    url(r'^login/$', views.login_view),
    url(r'^register/$', views.register_view),
    url(r'^logout/$', views.logout_view),

    url(r'^query/$', views.query),
    url(r'^storage/$', views.storage),
    url(r'^statistics/$', views.statistics),

    url(r'^query_commodity/$', views.query_commodity),
    url(r'^query_monitor/$', views.query_monitor),
    url(r'^query_warehouse/$', views.query_warehouse),
    url(r'^query_putlog/$', views.query_putlog),
    url(r'^query_outlog/$', views.query_outlog),

    url(r'^add_commodity/$', views.add_commodity),
    url(r'^add_monitor/$', views.add_monitor),
    url(r'^add_provider/$', views.add_provider),
    url(r'^add_purchasingagent/$', views.add_purchasingAgent),
    url(r'^add_warehouse/$', views.add_warehouse),
    url(r'^add_saler/$', views.add_saler),

    url(r'^delete_commodity/$', views.delete_commodity),
    url(r'^delete_monitor/$', views.delete_monitor),
    url(r'^delete_warehouse/$', views.delete_warehouse),
    url(r'^delete_putlog/$', views.delete_putLog),
    url(r'^delete_outlog/$', views.delete_outLog),

    url(r'^edify_commodity/$', views.edify_commodity),
    url(r'^edify_monitor/$', views.edify_monitor),
    url(r'^edify_warehouse/$', views.edify_warehouse),

    url(r'^$', views.login_view),
]