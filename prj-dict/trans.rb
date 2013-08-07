#!/usr/bin/env ruby

require 'uri'
require 'net/http'
require 'pp'
require 'json'
require 'fileutils'

def translate(line, sl, tl)
        url = "http://translate.google.cn/translate_a/t?client=t&hl=#{tl}&sl=#{sl}&tl=#{tl}&ie=UTF-8&oe=UTF-8&trs=1&sc=1&q=#{line}"
	uri = URI.parse URI::encode(url)
	r = Net::HTTP.get(uri)
	JSON::parse(r.gsub(/,+/, ',')).first.first.first
end

#	fail 'no filename' if not File.file? ARGV[0].to_s

#	FileUtils.cp ARGV[0], ARGV[0]+".out"
#	of = File.open ARGV[0]+".out", "w:UTF-8"
#	File.open ARGV[0], "r:UTF-8" do |infile|
#	infile.each_line do |line|
#	line.chomp!
	line = ARGV[0]
#	STDOUT.puts line
#	of.puts line
	tr = translate line, 'en', 'ch'
#	of.puts "#{tr}"
	#STDOUT.puts "#{tr}"
	STDOUT.print "#{tr}"
#	end
#	end
