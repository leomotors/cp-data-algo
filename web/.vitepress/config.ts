import { defineConfig } from "vitepress";

import dsItems from "./ds.g";
import algoItems from "./algo.g";
import quizItems from "./quiz.g";

export default defineConfig({
  lang: "th",
  title: "CP Data Algo",
  description: "Website containing my code for CP Data Algo",
  lastUpdated: true,
  outDir: "../dist",

  head: [
    [
      "link",
      {
        rel: "stylesheet",
        href: "https://fonts.googleapis.com/css?family=IBM+Plex+Sans+Thai:r,i,b,bi",
      },
    ],
  ],

  themeConfig: {
    footer: {
      message: "Released under the MIT License",
      copyright: "Copyright © 2023-2024 Nutthapat Pongtanyavichai",
    },
    socialLinks: [
      {
        icon: "github",
        link: "https://github.com/leomotors/cp-data-algo",
      },
    ],

    sidebar: [
      {
        collapsed: false,
        text: "Introduction",
        items: [
          {
            text: "vtwi;t",
            link: "/introduction/",
          },
        ],
      },
      {
        collapsed: false,
        text: "Data Struct Grader",
        items: dsItems,
      },
      {
        collapsed: false,
        text: "Algo Design Grader",
        items: algoItems,
      },
      {
        collapsed: false,
        text: "All Quiz",
        items: quizItems,
      },
    ],
  },
});
