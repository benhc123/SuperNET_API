var SPNAPI = (function(SPNAPI, $, undefined) {


    SPNAPI.pageContent.InstantDEX = function () {
        var site = "InstantDEX";
        SPNAPI.loadSiteAPI(site);
    };

    SPNAPI.pageContent.Pangea = function () {
        var site = "Pangea";
        SPNAPI.loadSiteAPI(site);
    };

    SPNAPI.pageContent.Jumblr = function () {
        var site = "Jumblr";
        SPNAPI.loadSiteAPI(site);
    };

    SPNAPI.pageContent.MGW = function () {
        var site = "MGW";
        SPNAPI.loadSiteAPI(site);
    };

    SPNAPI.pageContent.Atomic = function () {
        var site = "Atomic";
        SPNAPI.loadSiteAPI(site);
    };

      SPNAPI.pageContent.PAX = function () {
              var site = "PAX";
              SPNAPI.loadSiteAPI(site);
      };
      
      SPNAPI.pageContent.Tradebots = function () {
              var site = "Tradebots";
              SPNAPI.loadSiteAPI(site);
      };
              
    SPNAPI.pageContent.Wallet = function () {
        var site = "Wallet";
        SPNAPI.loadSiteAPI(site);
    };

    SPNAPI.pageContent.Debug = function () {

        $(".debuglog").show();
        debug_on = 1;

        $("html, body").animate({ scrollTop: $(document).height() }, 1000);


    };




    SPNAPI.loadSite = function (page, callback) {

        $(".page").hide();
        $("#"+page+'_page').show();

        $(".json_submit_url").html("");
        $(".api_formfill").html("");
        $(".api-panel-title").html("Panel Titel");

        $('.navigation[data-page=' + page + ']').addClass('active');

        if(SPNAPI.pageContent[page]) {
            SPNAPI.pageContent[page](callback);
        }

    };


    SPNAPI.loadSiteAPI = function (site) {

        $(".api-navpills").html('<ul class="nav nav-pills nav-stacked">'+
        '<li class="active '+site+'_pills"><a href="#">ALL</a></li>'+
        '</ul>');

        $.each(SPNAPI.methods[site], function (index, value) {

            $("."+site+"_pills").after('<li><a href="#" class="api_method" data-agent="'+site+'" data-method="'+value.method+'">'+value.method+'</a></li>');

        });

        $(".api_method").on("click", function (e) {
            e.preventDefault();

            var agent = $(this).data("agent");
            var method = $(this).data("method");

            $('.nav-pills li.active').removeClass('active');
            $(this).parent().addClass('active');

            var method_obj = SPNAPI.methods[agent].reduce(function (obj, methods) {
                if (methods.method == method) {
                    return obj.concat(methods);
                } else {
                    return obj;
                }
            }, []);

            SPNAPI.loadApiBox(agent, method_obj);


            $(".api_control").on("keypress change", function () {

                var input_value = $(this).val();
                var input_name = $(this).attr("name");

                var submit_url = $(".json_submit_url");
                //Change output JSON
                var json = submit_url.html();
                json = JSON.parse(json);
                json[input_name] = input_value;
                json = JSON.stringify(json);
                submit_url.html(json);

            });

        });

    };


    return SPNAPI;
}(SPNAPI || {}, jQuery));
