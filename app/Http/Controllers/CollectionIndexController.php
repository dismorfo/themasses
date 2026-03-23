<?php

namespace App\Http\Controllers;

use Illuminate\View\View;

class CollectionIndexController extends Controller
{
    public function index(): View
    {
        $displayTitle = 'Collection Index: ' . config('app.name');

        return view('collectionindex', [
            'displayTitle' => $displayTitle
        ]);

    }
}
