@extends('layouts.app')

@section('title', $displayTitle)
@section('body_class', 'ishome isnode page home')

@section('content')
    <x-page-shell>
            <div class="items">
                <div class="intro item itemwide">
                    <p>The Masses, a richly illustrated radical magazine, was published monthly in New York from 1911 until 1917, when it was suppressed by the government for its anti-war and anti-government perspective. The Masses blended art and politics and included fiction, nonfiction, poetry, and illustrations by many of the leading radical figures of the day. <a href="{{ route('about.index') }}" class="readmore" aria-label="Read more about The Masses">READ&nbsp;MORE…</a></p>
                </div>
                <div class="item itemspecial">
                    <div class="newsitem">
                        <div class="meta">
                            <div>
                                <span class="md_label">Title:</span>
                                <h1 class="md_title">{{ config('app.name') }}</h1>
                            </div>
                            <div>
                                <span class="md_label">Publisher:</span> <span>{{ config('app.publisher') }}</span>
                            </div>
                            <div class="md_subjects">
                                <span class="md_label">Subject:</span> {{ implode(', ', config('app.about')) }}
                            </div>
                            <div class="index_link meta-link">
                              <a class="readmore" href="/the_masses_index.pdf">
                                <span class="icon ext-link-icon" aria-hidden="true" role="presentation">
                                  <svg version="1.1" xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink" x="0px" y="0px" fill="#c50f3c" width="14" height="17" viewBox="0 0 30 40" style="enable-background:new 0 0 30 40;" xml:space="preserve">
                                  <path d="M14.2,20c-0.4-1.2-0.4-3.7-0.2-3.7C14.7,16.3,14.6,19.2,14.2,20z M14.1,23.7c-0.6,1.6-1.4,3.4-2.2,4.9
                                  	c1.4-0.5,3-1.3,4.9-1.7C15.8,26.1,14.8,25.1,14.1,23.7L14.1,23.7z M6.7,33.4c0,0.1,1-0.4,2.7-3.1C8.9,30.8,7.2,32.2,6.7,33.4z
                                  	 M19.4,12.5H30v25.6c0,1-0.8,1.9-1.9,1.9H1.9c-1,0-1.9-0.8-1.9-1.9V1.9C0,0.8,0.8,0,1.9,0h15.6v10.6C17.5,11.7,18.3,12.5,19.4,12.5z
                                  	 M18.8,25.9c-1.6-1-2.6-2.3-3.3-4.2c0.4-1.4,0.9-3.6,0.5-5c-0.4-2.3-3.3-2.1-3.7-0.5c-0.4,1.4,0,3.4,0.6,6c-0.9,2.2-2.2,5-3.2,6.7
                                  	c0,0,0,0,0,0c-2.1,1.1-5.7,3.5-4.3,5.3C5.8,34.8,6.6,35,7,35c1.4,0,2.8-1.4,4.8-4.8c2-0.7,4.2-1.5,6.2-1.8c1.7,0.9,3.7,1.5,5,1.5
                                  	c2.3,0,2.4-2.5,1.5-3.4C23.4,25.4,20.3,25.7,18.8,25.9z M29.5,8.2l-7.7-7.7C21.4,0.2,21,0,20.5,0H20v10h10V9.5
                                  	C30,9,29.8,8.6,29.5,8.2z M23.7,28.1c0.3-0.2-0.2-0.9-3.3-0.7C23.2,28.7,23.7,28.1,23.7,28.1z"></path>
                                  </svg>
                                </span><span>Collection index (PDF)</span> </a>
                            </div>
                            <div class="bobcat_record meta-link"><a target="_blank" class="readmore" href="https://search.library.nyu.edu/discovery/fulldisplay?docid=alma990027193850107871&amp;context=&amp;context=&amp;vid=01NYU_INST:NYU"><span class="icon" aria-hidden="true" role="presentation"><svg version="1.1" xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink" fill="#c50f3c" width="14" height="12" viewBox="0 0 32 32" aria-label="External Link">
                            <path d="M25.152 16.576v5.696q0 2.144-1.504 3.648t-3.648 1.504h-14.848q-2.144 0-3.648-1.504t-1.504-3.648v-14.848q0-2.112 1.504-3.616t3.648-1.536h12.576q0.224 0 0.384 0.16t0.16 0.416v1.152q0 0.256-0.16 0.416t-0.384 0.16h-12.576q-1.184 0-2.016 0.832t-0.864 2.016v14.848q0 1.184 0.864 2.016t2.016 0.864h14.848q1.184 0 2.016-0.864t0.832-2.016v-5.696q0-0.256 0.16-0.416t0.416-0.16h1.152q0.256 0 0.416 0.16t0.16 0.416zM32 1.152v9.12q0 0.48-0.352 0.8t-0.8 0.352-0.8-0.352l-3.136-3.136-11.648 11.648q-0.16 0.192-0.416 0.192t-0.384-0.192l-2.048-2.048q-0.192-0.16-0.192-0.384t0.192-0.416l11.648-11.648-3.136-3.136q-0.352-0.352-0.352-0.8t0.352-0.8 0.8-0.352h9.12q0.48 0 0.8 0.352t0.352 0.8z"></path>
                            </svg>
                            </span><span>Library Catalog</span></a>
                            </div>
                        </div>
                    </div>
                </div>
            </div>
            <div class="items all-thumbs">
                @foreach ($documents as $item)
                    <article class="item">
                        <div class="card">
                            <a href="/{{ $item['type'] }}/{{ $item['identifier'] }}/">
                                <div class="thumbs" role="presentation">
                                    <img src="/images/{{ $item['identifier'] }}.jpg" width="328" height="401" class="imgload" loading="lazy" alt="">
                                </div>
                                <div class="meta">
                                    <h1 class="md_title" aria-label="{{ $item['title'] }}">{{ $item['date_string'] }}</h1>
                                </div>
                            </a>
                        </div>
                    </article>
                @endforeach
                <article class="item empty-article" aria-hidden="true">
                    <div class="card">&nbsp;</div>
                </article>
                <article class="item empty-article" aria-hidden="true">
                    <div class="card">&nbsp;</div>
                </article>
                <article class="item empty-article" aria-hidden="true">
                    <div class="card">&nbsp;</div>
                </article>
            </div>
    </x-page-shell>
@endsection
