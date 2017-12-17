from django.conf.urls import url
from . import views

urlpatterns = [
    # url(r'^login/$', views.login_view),
    url(r'^register/$', views.register_view),
    url(r'^logout/$', views.logout_view),
    url(r'^login/$', views.login_view),

    url(r'^index/$', views.index),
    url(r'^transfer/$', views.transfer),
    url(r'^warehousing/$', views.warehousing),
    url(r'^selling/$', views.selling),

    url(r'^withdraw_putlog/$', views.withdraw_putLog),
    url(r'^withdraw_outlog/$', views.withdraw_outLog),

    url(r'^$', views.login_view),
]