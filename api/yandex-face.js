var __gWrapSoc=null;

function _resetSoc(A)
{
    __gWrapSoc=A.parentNode.parentNode.parentNode;
    _addScript("/dropcounters.js");
    return false
}

function socReset(A)
{
    if (A && __gWrapSoc) {
        __gWrapSoc.className="soc-wrap g-hidden";
        __gWrapSoc=null
            }
}

function upMailBox(C)
{
    if(C) {
        if(C.show) {
            var B="<";
            var A=C.email+"<b> "+B+"/b>@"+C.domain;
            $ya("place_usermail").innerHTML=A;
            if(parseInt(C.count)>0) {
                $ya("place_mct").style.display="";
                $ya("place_mailCount").innerHTML=C.count;
                $ya("place_mailText").innerHTML=C.countaccus;
            }
        }

    }
};

function probkiInit(f,c)
{
    function o(z)
    {
        return/^\s*$/.test(z);
    }

    function e(z)
    {
        var A = d.getValue(z);

        if(A === g) {
            return "";
        }
        else {
            return A;
        }
}

function k(B)
{
    if(B===g) {
        return null;
    }

    var E="";
    var F=B.childNodes;

    try {
        var C=new XMLSerializer();
        for(var A=0,z=F.length; A<z; A++) {
            E+=C.serializeToString(F[A]);
        }
    }
    catch(D) {
        try {
            for(var A=0,z=F.length; A<z; A++) {
                E+=F[A].xml;
            }
        }
        catch(D) {
            E=g;
        }
    }
    return E
}

// score suffix
function m(z)
{
    if(z<0||isNaN(z)) {
        return"";
    }
    else {
        if(z>10) {
            return" баллов";
        }
        else {
            return([" баллов"," балл"," балла"," балла"," балла"," баллов"," баллов"," баллов"," баллов"," баллов"," баллов"])[z];
        }
    }
}

function n(z)
{
    return n.dict[z.toLowerCase()]||z;
}

n.dict={ "дом":"домой","работа":"на работу","дача":"на дачу","институт":"в институт","университет":"в университет","универ":"в универ","юнивер":"в юнивер","яндекс":"в Яндекс!","учёба":"на учёбу","учеба":"на учебу","школа":"в школу","ясли":"в ясли","няня":"к няне","детсад":"в детсад","детский сад":"в детсад","больница":"в больницу","офис":"в офис","клуб":"в клуб","кино":"в кино","ресторан":"в ресторан","кафе":"в кафе","театр":"в театр","фитнес":"на фитнес","магазин":"в магазин","мама":"к маме","папа":"к папе","бабушка":"к бабушке","дедушка":"к дедушке","сестра":"к сестре","брат":"к брату","родители":"к родителям"};

// time length suffix
function l(A)
{
    var z="&#126;",B=0;
    if(isNaN(A)) {
        return"";
    }
    if(Math.floor(A/3600)>0) {
        z+=Math.floor(A/3600)+"&#32;ч&#32;";
    }
    B=Math.floor((A%3600)/60);
    if(B===0&&A>=60*60) {
        return z;
    }
    else {
        return z+B+"&#32;мин";
    }
}


// Return score by route estimation
function v(B,D,C)
{
    var z=1, F=C/1000;

    if(C<500) {
        z=0.5;
    }
    else {
        if(F<1) {
            z=0.75;
        }
        else {
            if (F>=15 && F<80) {
                z=(1/65)*(F-15)+1;
            }
            else {
                if(F>=80) {
                    z=2;
                }
            }
        }
    }

    var A=z*(D/B-1)*100,E=-1;
    if(A>=0) {
        E=0;
    }

    if(A>10) {
        E=1;
    }

    if(A>20) {
        E=2;
    }

    if(A>30) {
        E=3;
    }

    if(A>45) {
        E=4;
    }

    if(A>60) {
        E=5;
    }

    if(A>75) {
        E=6;
    }

    if(A>90) {
        E=7;
    }

    if(A>120) {
        E=8;
    }

    if(A>160) {
        E=9;
    }

    if(A>220) {
        E=10;
    }
    return E;
}

function u(z)
{
    $.ajax({ method:"get",url:i[z],cache:false,timeout:5000,success:
            function(A) {
                var C=null,E=null,D=null,B="http://maps.yandex.ru/router/1.x";

                if( A && A.documentElement && A.documentElement.getElementsByTagName("error").length == 0) {
                    if(A.documentElement.getElementsByTagNameNS) {
                        C=k(A.documentElement.getElementsByTagNameNS(B,"time")[0]);
                        E=k(A.documentElement.getElementsByTagNameNS(B,"jamsTime")[0]);
                        D=k(A.documentElement.getElementsByTagNameNS(B,"length")[0]);
                    }
                    else {
                        C=k(A.documentElement.getElementsByTagName("r:time")[0]);
                        E=k(A.documentElement.getElementsByTagName("r:jamsTime")[0]);
                        D=k(A.documentElement.getElementsByTagName("r:length")[0]);
                    }
                }
                a(C,E,D,z,true);
            } ,error:
            function() {
                if(arguments[1]=="timeout") {
                    this.timeout=2000;
                    this.error=function() {
                        a(null,null,null,z,false);
                    };
                    $.ajax(this);
                }
                else {
                    a(null,null,null,z,false);
                }
            },dataType:"xml";
        })
        }

function a(G,F,D,B,z)
{
d.$().find(".b-router .b-router__section").hide();
var I="b-router__indicator_red b-router__indicator_yellow b-router__indicator_green b-router__indicator_gray",J=
{
backgroundImage:"url(//img.yandex.net/i/widget/semaphores.png)"
}
;
if(G!==null&&F!==null)
{
if(z)
{
p[B].rTime=G;
p[B].jamsTime=F;
p[B].routeLength=D;
p[B].timestamp=new Date().getTime()
}
var C=v(G,F,D),H="",A="";
switch(true)
{
case F<30*60:H=l(F);
break;
case F>=30*60&&F<40*60:H="&#126;
полчаса";
break;
case F>=40*60&&F<50*60:H=l(Math.round(F/(5*60))*5*60);
break;
case F>=50*60&&F<80*60:H=l(Math.round(F/(10*60))*10*60);
break;
case F>=80*60&&F<100*60:H="&#126;
полтора&#32;
часа";
break;
case F>=100*60:H=l(Math.round(F/(15*60))*15*60);
break;
default:H=l(F);
break
}
if(C==0)
{
A="пробок нет"
}
else
{
if(C<0)
{
A=s
}
else
{
A=C+m(C)
}

}
var E="b-router__indicator_gray";
if(C>=7)
{
E="b-router__indicator_red"
}
else
{
if(C<7&&C>3)
{
E="b-router__indicator_yellow"
}
else
{
if(C<=3&&C>=0)
{
E="b-router__indicator_green"
}

}

}
d.$().find(".b-router .b-router__section_"+B).show().find(".b-router__rate").attr("href",x).find("strong").html(A).end().end().find(".b-router__data").html(H).end().find(".b-router__indicator").removeClass(I).addClass(E).css(J).end().find(".b-router__around").html(C>3?q[B]:"")
}
else
{
d.$().find(".b-router .b-router__section_"+B).find(".b-router__rate strong").html(s).end().find(".b-router__data").html("").end().find(".b-router__indicator").removeClass(I).addClass("b-router__indicator_gray").css(J).end().find(".b-router__around").html(q[B]).end().show()
}
d.hookStats()
}
function h()
{
if(p[j].timestamp>0&&(new Date().getTime())-p[j].timestamp<w&&p[j].rTime!=""&&p[j].jamsTime!=""&&p[j].routeLength!="")
{
a(p[j].rTime,p[j].jamsTime,p[j].routeLength,j)
}
else
{
u(j)
}

}
var d=Widget.Framework.get(f)||c,b=
{
gohome:[],gowork:[]
}
,r=
{
home:"",work:""
}
,y=
{
home:"",work:""
}
,i=
{
gohome:"",gowork:""
}
,x="",q=
{
gohome:"",gowork:""
}
,p=
{
gohome:
{
timestamp:0,rTime:null,jamsTime:null,routeLength:null
}
,gowork:
{
timestamp:0,rTime:null,jamsTime:null,routeLength:null
}

}
,w=4*60*1000,j="gohome",t=1,s="нет данных",g;
if(d===g)
{
return true
}
d.onload=function()
{
window.clearInterval(d.$().data("probkiInterval"));
if(e("workTransit")==="")
{
b.gowork=[]
}
else
{
b.gowork=e("workTransit").split("|")
}
if(e("homeTransit")==="")
{
b.gohome=[]
}
else
{
b.gohome=e("homeTransit").split("|")
}
r.home=e("homeGeo");
r.work=e("workGeo");
y.home=e("homeLabel");
y.work=e("workLabel");
if(window.location.href.indexOf("edit=1")!==-1)
{
d.$().find(".b-router__promo a,.b-router__setup").click(function(B)
{
if(wg&&wg.showEditForm&&f!==g)
{
B.preventDefault();
window.clearInterval(d.$().data("probkiInterval"));
wg.showEditForm(f)
}

}
)
}
if(r.home===""||r.work==="")
{
d.$().find(".b-router__promo").show();
return true
}
else
{
$.each(["gohome","gowork"],function(D,F)
{
var B=[],E=[],I=[],C="",J="/map_router/1.x/?",K="AE_AjkgBAAAAVhRKNwIAC8tjU2RrhP-ZqBu8wUeLshaL0DUAAAAAAAAAAABvwCsB0jR6VKSmbT2ZrfeIDgc8bg==~AIjAjkgBAAAAbw43bgIAgoFaZzyAbV54HVt9PueO4c4w-5gAAAAAAAAAAAA64IjoDNvFTVN2SEqaZO38eh_fMw==~AO0V1EoBAAAAXeYMcQIA4dz0va7f19syy0BH94hwX7A9UG0AAAAAAAAAAAD3lBnSWu6wycdxwJyqkjrsJq3h3A==";
$.merge(B,b[F]);
B.unshift(F==="gowork"?r.home:r.work);
B.push(F==="gowork"?r.work:r.home);
C=B.join("~");
for(var H=1,G=b[F].length;
H<=G;
H++)
{
E.push(H)
}
i[F]=J+"rll="+C+"&output=time";
if(E.length>0)
{
i[F]+="&via="+E.join(",")
}
i[F]+="&key="+K;
if(F=="gohome")
{
I=[r.work,r.home]
}
else
{
I=[r.home,r.work]
}
q[F]='<a rev="bypass" href="http://maps.yandex.ru/?rt='+encodeURIComponent(I.join("~"))+'&amp;
l=map,trf,cmr">объезд<\/a>'
}
);
var z=r.home.split(","),A=r.work.split(",");
x="http://maps.yandex.ru/?l=map,trf,cmr&ll="+(parseFloat(z[0])+parseFloat(A[0]))/2+","+(parseFloat(z[1])+parseFloat(A[1]))/2+"&spn="+Math.abs(z[0]-A[0])*1.1+","+Math.abs(z[1]-A[1])*1.1;
d.$().find(".b-router__promo").hide().end().find(".b-router__section .b-router__rate").attr("href",x).end();
new Image().src="//clck.yandex.ru/click/dtype=stred/pid=132/cid=2919/path=probki.show/rnd="+((new Date()).getTime()+Math.round(Math.random()*100))+"/*http://www.yandex.ru"
}
t=new Date().getHours();
if(o(y.home)&&o(y.work))
{
if(t>=15||t<=3)
{
j="gohome"
}
else
{
j="gowork"
}

}
else
{
if(!o(y.home))
{
d.$().find(".b-router__section_gohome .b-router__now, .b-router__section_gowork .b-router__where").text(n(y.home))
}
if(!o(y.work))
{
d.$().find(".b-router__section_gohome .b-router__where, .b-router__section_gowork .b-router__now").text(n(y.work))
}

}
d.$().find(".b-router .b-router__where").click(function(C)
{
var B=$(this).closest(".b-router__section");
if(B.hasClass(".b-router__section_gohome"))
{
B.hide().closest(".b-router").find(".b-router__section_gowork").show();
j="gowork"
}
else
{
B.hide().closest(".b-router").find(".b-router__section_gohome").show();
j="gohome"
}
h()
}
);
h();
d.$().data("probkiInterval",window.setInterval(function()
{
h()
}
,5*60*1000))
}

}
;

