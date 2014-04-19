---
layout: post
title: "用Geek的方式来写博客(1)：在Github上搭建Octopress"
date: 2013-08-01 10:45
comments: true
keywords: Octopress
description:
categories: [Octopress]
tags: [Octopress, Blog]
published: true
---

听说Octopress还是去年的时候，原因是我宿舍隔壁一哥们买了个域名。因为我一直有开个博客的想法，但不知道哪家提供的服务比较好，于是就去问了一下，没想到他说他把他的博客托管在了Github上。没问明白，我回宿舍后就Google了一下，于是发现了Octopress这个Ruby项目。

这种编写博客的方式立即就吸引了我。那段时间还挣扎在VIM和Emacs之间，对于Markdown也是久闻大名，当即决定，就是这货了！

<!-- more -->

当时对于Linux和Github都还算不上熟悉，一切都还在摸索的阶段，折腾了几下发完一篇Hello World之后就放下了。一直到这个暑假，因为各种原因（再次-_-）下定决心要开一个博客，于是顿时回想起了Octopress。做了一个调查后，我决定换用使用Python编写的Pelican来搭建博客，因为相对来说我对Python更有好感，不过用Pelican搭建好博客后在deploy的阶段老是遇到莫名其妙的字符编码错误，Google上搜索不到任何相关的资料，折腾了一天后连第一篇博文都没发到网上。

于是我又把目光转回了Octopress。在Github的页面上看了看发现大家还是挺活跃的，最近的一次更新在十多天之前，于是决定还是用Octopress来搭建博客。

Octopress的默认主题我觉得很不错，没有什么修改的动力，不过仍旧安装了一些插件，进行了一些小修小补，这里把安装过程记录下来，发到网上，供广大和我一样刚接触Octopress的朋友们参考一下吧。

### 1.安装Octopress
这里给出[官方教程](http://octopress.org/docs/setup/)的链接，本博文的教程和官方的几乎一致，不过在一些细节上会进行更详细的解说。

如果你还不知道git是什么的话，那么[这里](http://www.open-open.com/lib/view/open1328069609436.html)有一份中文详细教程，可以让你对git有一个大致全面的了解。

首先，搭建的环境是在Linux下（我使用的是Archlinux）。据说因为ruby的发展过于迅猛，导致了短时间内大量版本层出不穷，各种ruby脚本基于各种不同的ruby版本被写出来，这就导致了版本依赖方面略微复杂。所以一般并不推荐直接安装ruby，而是安装[rbenv](http://octopress.org/docs/setup/rbenv/)或者[RVM](http://octopress.org/docs/setup/rvm/)，用它们来进行ruby的版本控制。

上面已经给出了`rbenv`和`RVM`的安装指南链接，不过这里还是稍微讲一下，当然是针对我用的`rbenv`。

```bash 安装rbenv
cd
git clone git://github.com/sstephenson/rbenv.git .rbenv
echo 'export PATH="$HOME/.rbenv/bin:$PATH"' >> ~/.zshrc #我使用的是zsh，bash或其他shell的用户需要进行相应更改
echo 'eval "$(rbenv init -)"' >> ~/.zshrc
git clone git://github.com/sstephenson/ruby-build.git ~/.rbenv/plugins/ruby-build
source ~/.zshrc
```

对于最新版的Octopress来说，使用`rbenv`进行安装的话需要安装`ruby-1.9.3-p194`，而不是官方所说的`1.9.3-p0`。更新版的ruby是否能用，我没有进行过尝试。

```bash 安装ruby
rbenv install 1.9.3-p194
rbenv rehash
```

运行`ruby --version`查看是否已经成功安装了指定版本的ruby。

```bash 查看ruby版本
$ ruby --version
rbenv: ruby: command not found

The `ruby' command exists in these Ruby versions:
  1.9.3-p194
```

ruby搞定了，接下来就该把Octopress从Github上拖回来了。

```bash Clone Octopress
git clone git://github.com/imathis/octopress.git MyBlog #MyBlog修改为你想要的名字
cd MyBlog
```

然后安装Octopress运行所必需的依赖。

```bash 安装Octopress的依赖
gem install bundler
rbenv rehash
bundle install
```

此时，Octopress的环境已经被安装好了，下面是安装Octopress的默认主题。

```bash 安装Octopress主题
rake install
```

至此，Octopress就已经被部署好了。

注意上面`gem install bundler`有时候会遇到`Connection Refused`的情况，不明原因，不过加上代理服务器后就成功安装了。如果你也遇到了相关的问题，那么就找一个代理服务器，或者自己搭建一个`GoAgent`科学上网，这里就不详细叙述了，一切请Google吧。

```bash Gem使用代理
gem install bundler --http-proxy http://localhost:8087
```
### 2.配置Octopress
`Octopress`的根目录下有四个配置文件：

```text Octopress配置文件
_config.yml       # Main config (Jekyll's settings)
Rakefile          # Configs for deployment
config.rb         # Compass config
config.ru         # Rack config
```

一般来说其中只有两个需要进行更改，那就是`_config.yml`和`Rakefile`。

首先我们来看`_config.yml`，一般来说需要更改的地方如下：

```text _config.yml
url: http://yoursite.com
title: My Octopress Blog
subtitle: A blogging framework for hackers.
author: Your Name
simple_search: http://google.com/search
description:
```

将其中的信息换成你的信息，比如：

```text _config.yml
url: http://cryonyx.github.com
title: Cryonyx
subtitle: Geek is an attitude.
author: Cryonyx
simple_search: http://google.com/search
description: This is my personal blog.
```

要开启博客的评论功能的话，请去[Disqus](http://disqus.com/)注册一个帐号，然后把相应的站点`shortname`填写到相关位置。

```text disqus
# Disqus Comments
disqus_short_name: Your Site's Short Name
disqus_show_comment_count: false
```

更详细（其实也不详细）的介绍请看[官方文档](http://octopress.org/docs/configuring/)。

### 2.使用搭建好的博客发文
做好了基础配置，那么下面就该发布一篇新的文章了来试试了，我当初发布了第一篇Hello World。发布新文章的命令是：

```bash 发布新文章
$ rake new_post["title"]
```

这条命令会自动在`source/_post`里生成一个名为`yyyy-mm-dd-post-title.markdown`的文件，然后你就可以用自己喜欢的编辑器对其进行修改。

假设我们`rake new_post["Hello World"]`，那么我们会在`source/_post`下得到`2013-08-01-hello-world.markdown`，Octopress把文件名自动转换为了小写，而且空格也使用`-`代替，测试发现，点`.`也会被`dot`所代替。

如果不对`_config.yml`文件中的`permalink`进行更改的话，那么这篇博文的地址就是`http://site.com/blog/2013/08/01/hello-world/index.html`。虽然你`rake new_post["title"]`时的`title`将作为你的文章的默认标题，但文章的链接地址和它有关，文章的具体标题内容和它无关，后面可以对文章的具体标题进行修改。

我们打开新建的文件，可以看到如下的被称为`yaml front matter`内容，它包含了文章的基本信息，可以帮助`Jkelly`正确生成你的文章页面等信息：

```yaml source/_post/2013-08-01-hello-world.markdown
---
layout: post
title: "Hello World"
date: 2013-08-01 11:12
comments: true
categories:
---
```

其中`layout: post`是指调用`source/_layout/post.html`作为文章模板，`title`无疑就是文章的标题，默认值是新建文章填入的字符。如果不想让文章被评论的话，可以设置`comments`为`false`。而`categories`自然就是给文章的分类了。

其实可以使用的属性项远不止如此，比如我们还可以加入`keywords`，`description`，这样可以生成网页的`meta`信息，帮助推广。另外如果一篇文章只是草稿，还没有到发布的时候，可以加入`published: false`，这样文章就不会显示出来了（其实连`generate`都省了）。

每次都手动输入略显麻烦，我们可以稍微修改一下`Rakefile`，找到第106行左右的区域：

```rb Rakefile
  puts "Creating new post: #{filename}"
  open(filename, 'w') do |post|
    post.puts "---"
    post.puts "layout: post"
    post.puts "title: \"#{title.gsub(/&/,'&amp;')}\""
    post.puts "date: #{Time.now.strftime('%Y-%m-%d %H:%M')}"
    post.puts "comments: true"
    post.puts "categories: "
    post.puts "---"
```

一目了然，这就是默认的yaml信息模板，相应地进行更改就好，比如加上`post.puts "published: true"`。

还可以添加上`tags`，不过tag功能需要另外安装插件，这会在后面一篇博文中提到。

另外需要提醒一下的是，`rake_new_post`时不能使用中文作为标题：

```bash rake new_post使用中文的错误提示
$ rake new_post["测试中文标题"]
rake aborted!
### You haven't set anything up yet. First run `rake install` to set up an Octopress theme.

Tasks: TOP => new_post
(See full trace by running task with --trace)
```

那么博客文章能不能使用中文标题呢？当然是可以的，`rake new_post`的时候给文章起一个英文名，或者用拼音代替，然后修改`markdown`文件里的`title`即可以给文章设置中文名了。

另外一个需要注意的地方是，每一个冒号后面都必须要有一个`空格`，否则会`Build Failed`。

在`---`下方写上博客的内容，比如再写一句"Hello World!"，这篇博文就算完成了，保存吧。

然后在博客目录`rake generate`，这条命令会自动将所有`markdown`文件转换为`html`文件。转换完成后`rake preview`，即可用网址`http://localhost:4000`在浏览器中预览博客的样子。当`rake preview`运行的时候，可以对文章的`markdown`文件继续进行修改，不用再次`rake generate`，几秒钟的延迟后更改就会体现出来。不过新增文章等一部分操作，都需要再次`rake generate`才能正确预览。

Octopress博客默认有两个页面，一个是"Blog"，一个是"Archive"，如果想要新增一个页面的话，就需要用`rake new_page["page"]`命令：

```bash
rake new_page[About]
```

这会在`source`目录下建立一个`About`文件夹，其中包含有`index.markdown`，可以对其进行修改。

但是新增的页面并不会自动地显示到导航栏上去，还需要进行一定的修改。找到`source/_includes/custom/navigation.html`：

```html
<ul class="main-navigation">
  <li><a href="{{ root_url }}/">Blog</a></li>
  <li><a href="{{ root_url }}/blog/archives">Archives</a></li>
</ul>
```

在合适的位置添加上`<li><a href="{{ root_url }}/about">About</a></li>`即可。

另外博客默认是首页显示每一篇博文所有内容的，如果你不想这么做，那么就需要在博文的合适位置加上`<!-- more -->`，这可以让首页博文的内容在这里截止，并显示`Read On`，也就是点击继续阅读。


### 3.将博客推送到Github
我们现在搭建好了博客，也发了一篇文章，不过还没有把博客部署到github上。

首先你需要一个Github的帐号，并且创建一个名为`username.github.com`的repository。

记住，名字必须是`username.github.com`，只有这样才能以网址`username.github.com`打开你的博客。

然后输入以下命令：

```bash
rake setup_github_pages #它会询问信息，并且进行相应的操作。按照提示进行就好。
rake generate
rake deploy
```

`setup_github_pages`时会让你输入你的repository的git地址，它给出了一个示例是`https://github.com/username/username.github.io`，但其实不能这么输入，会报错，你得换成`https://github.com/username/username.github.com.git`。

这样就把网站文件发送到你的repository了，不过目前仅仅是把生成好的网页文件发送了过去，octopress的一套东西包括markdown文件都还在本地呢，这样可不行。

```bash
git add .
git commit -m "Backup source"
git push origin source
```

现在就大功告成了，这在你的repository下新建了一个source分支，用来保存你所有的源文件。以后要是本地文件丢失了，恢复就靠它了。

现在，打开浏览器，输入网址`http://username.github.com`，你应该就能看到你的博客了～欢呼吧。

什么？404？There isn't a GitHub Page here？没关系，一般情况下这是因为延迟，稍等几分钟再看就好了。如果还是不行的话，检查一下上面的步骤，到`https://github.com/username/username.github.com`看看是否已经deploy成功，然后再`rake deploy`一次吧。

下面一篇博文将会讲到一些插件的使用，为博客添加上更丰富的功能，以及在使用这些插件中所遇到的一些问题和解决方法。
