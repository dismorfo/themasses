@extends('layouts.app')

@section('title', $displayTitle)
@section('body_class', 'ispage pages page')

@section('content')
    <x-page-shell>
            <h1 class="page-title">About</h1>
            <div class="content">
                <p><em>The Masses</em>, a richly illustrated radical magazine, was published monthly in New York from 1911 until 1917, when it was suppressed by the government for its anti-war and anti-government perspective. The Masses blended art and politics and included fiction, nonfiction, poetry, and illustrations by many of the leading radical figures of the day.</p>
                <p> This digital edition reproduces the holdings of the Tamiment Library &amp; Robert F. Wagner Labor Archives at New York University. To contact the library, please email <a href="mailto:special.collections@nyu.edu">special.collections@nyu.edu</a>.</p>
            </div>
    </x-page-shell>
@endsection
