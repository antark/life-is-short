package test;

import java.io.UnsupportedEncodingException;
import java.net.URI;
import java.net.URISyntaxException;
import java.net.URLDecoder;
import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class URIUtils {
    private static final String PARAMETER_SEPARATOR = "&";
    private static final String NAME_VALUE_SEPARATOR = "=";
    private static final String DEFAULT_CHARSET = "ISO-8859-1";

    public static String getParameter(String url, String key){
        return getParameter(url, key, DEFAULT_CHARSET);
    }

    public static String getParameter(String url, String key, String encoding){
        Map<String, String> result = parseParameters(url, encoding);
        if(result == null){
            return null;
        }else{
            return result.get(key);
        }
    }

    public static String getQueryParameter(String query, String key){
        return getQueryParameter(query, key, DEFAULT_CHARSET);
    }

    public static String getQueryParameter(String query, String key, String encoding){
        Map<String, String> result  = parse(query, encoding);
        if(result == null){
            return null;
        }else{
            return result.get(key);
        }
    }

    private static Map<String, String> parseParameters(String url, String encoding){
        Map<String, String> result = new HashMap<String, String>();

        URI uri = null;
        try{
            uri = new URI(url);
        }catch(URISyntaxException e) {
            throw new IllegalArgumentException(e);
        }

        String query = uri.getRawQuery();
        if(query != null && !query.isEmpty()){
            result = parse(query, encoding);
        }
        return result;
    }

    private static Map<String, String> parse(String query, String encoding){
        Map<String, String> result = new HashMap<String, String>();

        Scanner scanner = new Scanner(query);
        scanner.useDelimiter(PARAMETER_SEPARATOR);
        while(scanner.hasNext()){
            String[] nameValue = scanner.next().split(NAME_VALUE_SEPARATOR);
            if(nameValue.length <= 0 || nameValue.length > 2){
                continue;
            }

            String name = decode(nameValue[0], encoding);
            String value = null;
            if(nameValue.length == 2){
                value = decode(nameValue[1], encoding);
            }
            result.put(name, value);
        }
        return result;
    }

    private static String decode(final String content, final String encoding){
        try{
            return URLDecoder.decode(content, encoding != null ? encoding : DEFAULT_CHARSET);
        }catch(UnsupportedEncodingException e){
            throw new IllegalArgumentException(e);
        }
    }

    public static void main(String[] args){
        String url = "http://www.name.lrj/?id=1234";
        String id = URIUtils.getParameter(url, "id");
        System.out.println(id);    // 1234

        String query = "name=zhangsan&age=20";
        String age = URIUtils.getQueryParameter(query, "age");
        System.out.println(age);
    }
}
