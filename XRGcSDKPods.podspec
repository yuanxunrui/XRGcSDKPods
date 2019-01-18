#
# Be sure to run `pod lib lint XRGcSDKPods.podspec' to ensure this is a
# valid spec before submitting.
#
# Any lines starting with a # are optional, but their use is encouraged
# To learn more about a Podspec see https://guides.cocoapods.org/syntax/podspec.html
#

Pod::Spec.new do |s|
  s.name             = 'XRGcSDKPods'
  s.version          = '0.1.0'
  s.summary          = '这是一个简单的介绍'

# This description is used to generate tags and improve search results.
#   * Think: What does it do? Why did you write it? What is the focus?
#   * Try to keep it short, snappy and to the point.
#   * Write the description between the DESC delimiters below.
#   * Finally, don't worry about the indent, CocoaPods strips it!

  s.description      = <<-DESC
这是一个复杂的介绍，详细的信息可以写在这里
                       DESC

  s.homepage         = 'https://github.com/yuanxunrui/XRGcSDKPods'
  # s.screenshots     = 'www.example.com/screenshots_1', 'www.example.com/screenshots_2'
  s.license          = { :type => 'MIT', :file => 'LICENSE' }
  s.author           = { 'yuanxunrui' => 'yxruisoft@sina.com' }
  s.source           = { :git => 'https://github.com/yuanxunrui/XRGcSDKPods.git', :tag => s.version.to_s }
  # s.social_media_url = 'https://twitter.com/<TWITTER_USERNAME>'

  s.ios.deployment_target = '9.0'

  # s.source_files = 'XRGcSDKPods/Classes/**/*'
  s.vendored_frameworks = 'XRGcSDKPods/Classes/*.framework'
  s.libraries = "c++"
  # s.resource_bundles = {
  #   'XRGcSDKPods' => ['XRGcSDKPods/Assets/*.png']
  # }

  # s.public_header_files = 'Pod/Classes/**/*.h'
  s.frameworks = 'UIKit', 'Foundation'
  # s.dependency 'AFNetworking', '~> 2.3'
end
