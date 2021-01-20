## Platform
Platform

## Release iMES登录
配置权限，IMES登录账号 账号：20165185 密码：111111

## RestClient
IRestClient restClient = new RestClient();
restClient.ContentType = ContentType.APPLICATION_JSON;
IRestResponse restResponse = restClient.Get("http://www.baidu.com");
IRestResponse restResponse = restClient.Post("http://www.baidu.com", "{}");
string body = restResponse.GetResponseBody();